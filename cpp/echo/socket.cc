#include "socket.hpp"

namespace Network {
    Socket::Socket(SocketType t): fd_{ buildListerSocket() } {
        memset(&address_, 0, sizeof(address_));
    };

    Socket::Socket(): Socket(SocketType::Stream) {};

    // sockaddr_in...
    Socket::Socket(int fd): fd_{fd} {};

    void Socket::close() { ::close(fd_); }

    const int Socket::bind(const std::string host, const uint port) {
        int rv = 0;
        rv = sockaddrIn(host, port);
        if (rv < 0) {
            return rv;
        }

        rv = ::bind(fd_, reinterpret_cast<const sockaddr*>(&address_), sizeof(address_));
        if (rv < 0) {
            logger->error("bind call failed: {}", strerror(errno));
            return rv;
        }

        return 0;
    }

    const int Socket::connect(const std::string host, const uint port) {
        int rv = 0;
        rv = sockaddrIn(host, port);
        if (rv < 0) {
            return rv;
        }

        rv = ::connect(fd_, reinterpret_cast<const sockaddr*>(&address_), sizeof(struct sockaddr));
        if (rv < 0) {
            logger->error("connect failed: {}", strerror(errno));
            return rv;
        }

        return 0;
    }

    // only ipv4 support
    const int Socket::sockaddrIn(const std::string host, const uint port) {
        address_.sin_family = AF_INET;
        address_.sin_port = htons(port);
        int rc = ::inet_pton(AF_INET, host.data(), &address_.sin_addr);
        if (1 != rc) {
            logger->error("Invalid ipv4 address '{}'", host);
            return -1;
        }
        return 0;
    };

    namespace socket {
        int Buffer::add(const void* data, uint64_t size) {
            return evbuffer_add(buffer_, data, size);
        }

        int Buffer::write(const int fd) {
            const uint64_t MaxSlices = 16; // 16?
            RawSlice slices[MaxSlices];
            const uint64_t num_slices = std::min(getRawSlice(slices, MaxSlices), MaxSlices);
            iovec iov[num_slices];

            uint64_t write_count = 0;
            for (uint64_t i = 0; i < num_slices; i++) {
                if (slices[i].mem_ == nullptr || slices[i].len_ == 0) {
                    continue;
                }
                iov[i].iov_base = slices[i].mem_;
                iov[i].iov_len = slices[i].len_;
                write_count++;
            }
            if (write_count == 0) {
                return 0;
            }

            const ssize_t rc = writev(fd, iov, write_count);
            if (rc > 0) {
                drain(static_cast<uint64_t>(rc));
            }

            return rc;
        }

        void Buffer::takeIn(Buffer& b) {
            int rc = evbuffer_add_buffer(buffer_, b.buffer_);
            if (rc != 0) {
                logger->error("failed taken in {}", rc);
            }
        }

        void Buffer::commit(RawSlice* iovecs, uint64_t const size) {
            int ret = evbuffer_commit_space(buffer_, reinterpret_cast<evbuffer_iovec*>(iovecs), size);
            if (ret != 0) {
                logger->error("evbuffer_commit_sapce failed");
                exit(1);        // XXX
            }
        }

        int Buffer::read(const int fd, const uint64_t max_length) {
            const uint64_t MaxSlices = 2;
            RawSlice slices[MaxSlices];
            const uint64_t num_slices = reserve(max_length, slices, MaxSlices);
            iovec iov[num_slices];
            uint64_t num_bytes_to_read = 0;

            uint64_t i = 0;
            // TODO
            for (; i < num_slices; i++) {
                iov[i].iov_base = slices[i].mem_;
                const size_t len = std::min(slices[i].len_, static_cast<size_t>(max_length - num_bytes_to_read));
                iov[i].iov_len = len;
                num_bytes_to_read += max_length;
            }

            const ssize_t rc = ::readv(fd, iov, static_cast<int>(i));
            if (rc < 0) {
                return rc;
            }

            uint64_t num_to_commit = rc;
            uint64_t j = 0;
            while (num_to_commit > 0) {
                slices[j].len_ = std::min(slices[j].len_, static_cast<size_t>(num_to_commit));
                num_to_commit -= slices[j].len_;
                j++;
            }

            commit(slices, j);
            return rc;
        }

        void Buffer::drain(const uint64_t len) {
            if (len <= 0) {
                puts("drain must not call with negative value");
                exit(1);
            }

            int rc = evbuffer_drain(buffer_, len);
            if (rc != 0) {
                puts("drain error %s");
                exit(1);
            }
        }

        uint64_t Buffer::reserve(uint64_t const length, RawSlice* iovecs, uint64_t const iovecs_num) {
            int ret = evbuffer_reserve_space(buffer_, length, reinterpret_cast<evbuffer_iovec*>(iovecs), iovecs_num);
            if (ret < 0) {
                printf("%d\n", ret);
                exit(1);
            }
            return ret;
        }
    }

    BufferedSocket::BufferedSocket(SocketPtr socket):
        read_buffer_{std::make_unique<socket::Buffer>()}, write_buffer_{std::make_unique<socket::Buffer>()}, socket_{std::move(socket)} {}

    BufferedSocket::BufferedSocket(int fd): BufferedSocket(std::make_unique<Socket>(fd)) {}

    void BufferedSocket::close() { socket_.get()->close(); }

    int BufferedSocket::write(const void* data, uint64_t size) { return write_buffer_.get()->add(data, size); }

    int BufferedSocket::flush() {
        auto fd = socket_.get()->fd();
        return write_buffer_.get()->write(fd);
    }

    // XXX
    IoResult BufferedSocket::read() {
        uint64_t bytes_read = 0;
        bool end_stream = false;
        bool need_close = false;

        auto fd = socket_.get()->fd();
        while(true) {
            int rc = read_buffer_.get()->read(fd, 65535);
            SPDLOG_TRACE(logger, "read bytes is {}",rc);

            if (rc == 0) {
                end_stream = true;
                break;
            } else if (rc < 0){
                if (errno != EAGAIN) {
                    need_close = true;
                }
                break;
            } else {
                bytes_read += rc;
            }
        }

        return {bytes_read, need_close, end_stream};
    }

    void BufferedSocket::drain(const uint64_t len) {
        return read_buffer_.get()->drain(len);
    }

    bool BufferedSocket::needFlush() {
        return (write_buffer_.get()->length() != 0);
    };

    IoResult BufferedSocket::onRead(SocketReadCallback cb) {
        Network::IoResult result = read();
        SPDLOG_TRACE(logger, "fd={} is read-ready and receives data is {} bytes", fd(), result.bytes_processed_);

        auto read_buffer = read_buffer_.get();
        if (result.bytes_processed_ > 0) {
            uint64_t slice_size = read_buffer_->getAvailableSliceCount();
            RawSlice slices[slice_size];
            read_buffer_->getRawSlice(slices, slice_size);

            for (auto s : slices) {
                cb(static_cast<const uint8_t*>(s.mem_), s.len_);
            }

            read_buffer->drain(read_buffer->length());
        }

        return result;
    }
}
