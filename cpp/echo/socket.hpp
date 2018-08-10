#pragma once

#include <memory>
#include <string>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <functional>

#include "event2/buffer.h"

#include "logger.hpp"

namespace Network {
    enum class SocketType { Stream, Datagram };

    static const int buildSocketFromType(SocketType type) {
        int flags = 0;
        if (type == SocketType::Stream) {
            flags |= SOCK_STREAM;
        } else {
            flags |= SOCK_DGRAM;
        }

        int fd = socket(AF_INET, flags, 0);
        fcntl(fd, F_SETFL, O_NONBLOCK); // macos does not have SOCK_NONBLOCK
        return fd;
    }

    static const int buildListerSocket() {
        int fd = buildSocketFromType(SocketType::Stream);

        int on = 1;
        int rc = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (rc) {
            logger->error("setsockopt returns", rc);
            return -1;
        }

        return fd;
    }

    class Socket {
    public:
        Socket(int fd);
        Socket(SocketType t);
        Socket();
        int fd() const { return fd_; }
        void close();
        // change new name of socket? to identify binded socket and connected socket
        const int bind(const std::string host, const uint port);
        const int connect(const std::string host, const uint port);
        const int sockaddrIn(const std::string host, const uint port);

    private:
        sockaddr_in address_;
        int fd_;
    };

    using SocketPtr = std::unique_ptr<Socket>;

    struct RawSlice {
        void* mem_ = nullptr;
        size_t len_ = 0;
    };

    // RawSlice is the same structure as evbuffer_iovec. This was put into place to avoid leaking
    // libevent into most code since we will likely replace evbuffer with our own implementation at
    // some point. However, we can avoid a bunch of copies since the structure is the same.
    static_assert(sizeof(RawSlice) == sizeof(evbuffer_iovec), "RawSlice != evbuffer_iovec");
    static_assert(offsetof(RawSlice, mem_) == offsetof(evbuffer_iovec, iov_base),
                  "RawSlice != evbuffer_iovec");
    static_assert(offsetof(RawSlice, len_) == offsetof(evbuffer_iovec, iov_len),
                  "RawSlice != evbuffer_iovec");

    namespace socket {
        class Buffer {
        public:
            Buffer(): buffer_{evbuffer_new()} {}
            Buffer(evbuffer* buffer): buffer_{ buffer } {};
            Buffer(const void* data, const uint64_t length): Buffer {} {
                add(data, length);
            }
            // ~Buffer() { evbuffer_free(buffer_); }

            int add(const void* data, uint64_t size);
            int write(const int fd);
            int read(const int fd, const uint64_t max_length);

            void drain(const uint64_t len);
            void commit(RawSlice* iovecs, uint64_t const size);
            uint64_t length() const { return evbuffer_get_length(buffer_); };
            uint64_t getAvailableSliceCount() { return getRawSlice(nullptr, 0); }
            uint64_t getRawSlice(RawSlice* out, uint64_t size)  { return evbuffer_peek(buffer_, -1, nullptr, reinterpret_cast<evbuffer_iovec*>(out), size); }
            evbuffer* buffer() { return buffer_; }
            void takeIn(Buffer& b);
        private:
            uint64_t reserve(uint64_t const length, RawSlice* iovecs, uint64_t const iovecs_num);
            evbuffer* buffer_;
        };

        using BufferPtr = std::unique_ptr<Buffer>;
    }

    struct IoResult {
        uint64_t bytes_processed_;
        bool need_close_;
        bool end_stream_read_;
    };

    using SocketReadCallback = std::function<int(const uint8_t *data, size_t len)>;

    class BufferedSocket {
    public:
        BufferedSocket(SocketPtr socket);
        BufferedSocket(int fd);

        // separate write/read ?
        int write(const void* data, uint64_t size);

        bool needFlush();
        int flush();

        IoResult onRead(SocketReadCallback cb);

        void drain(const uint64_t len);

        int fd() const { return socket_->fd(); }
        void close() ;

    private:
        IoResult read();

        socket::BufferPtr read_buffer_;
        socket::BufferPtr write_buffer_;

        SocketPtr socket_;
    };

    using BufferedSocketPtr = std::unique_ptr<BufferedSocket>;
}
