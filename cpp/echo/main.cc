#include "main.hpp"

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

    return -1;
}

void Buffer::commit(RawSlice* iovecs, uint64_t const size) {
    int ret = evbuffer_commit_space(buffer_, reinterpret_cast<evbuffer_iovec*>(iovecs), size);
    if (ret != 0) {
        puts("evbuffer_commit_sapce failed");
        exit(1);
    }
}

int Buffer::read(const int fd, const uint64_t max_length) {
    std::cout << "[read] target file descriptor " << fd <<  "\n";
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
        // TODO: if EAGAIN, then more data would read.
        std::cout << "[read] " << strerror(errno) <<  "\n";
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

static void accept_conn_cb(evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx) {
    event_base *base = evconnlistener_get_base(listener);
    std::cout << "[accept_conn_cb] \n";
    ServerConnection *conn = new ServerConnection(base, fd);
}

static void accept_error_cb(struct evconnlistener *listener, void *ctx) {
    struct event_base *base = evconnlistener_get_base(listener);
    int err = EVUTIL_SOCKET_ERROR();
    fprintf(stderr, "Got an error %d (%s) on the listener. "
            "Shutting down.\n", err, evutil_socket_error_to_string(err));

    event_base_loopexit(base, NULL);
}

SocketEvent::SocketEvent(event_base* base, int fd, SocketEventCb cb, uint32_t events): base_{base}, cb_{cb}, fd_{fd} {
    assignEvents(events);
    event_add(&raw_event_, nullptr);
}

void SocketEvent::assignEvents(uint32_t events) {
    uint32_t what =
        EV_PERSIST |
        (events & SocketEventType::Read ? EV_READ : 0) |
        (events & SocketEventType::Write ? EV_WRITE : 0) |
        (events & SocketEventType::Closed ? EV_CLOSED : 0);
    raw_event_ = *event_new(base_, fd_, what,
                            [](evutil_socket_t fd, short what, void* arg) -> void {
                                SocketEvent* e = static_cast<SocketEvent *>(arg);
                                uint32_t events = 0;
                                if (what & EV_READ) {
                                    events |= SocketEventType::Read;
                                }

                                if (what & EV_WRITE) {
                                    events |= SocketEventType::Write;
                                }

                                if (what & EV_CLOSED) {
                                    events |= SocketEventType::Closed;
                                }

                                e->cb_(events);
                            },
                 this);
}

ServerConnection::ServerConnection(event_base* base, evutil_socket_t fd): fd_{fd} {
    a_ = 100;
    std::cout << "[init ServerConnection]\n";
    auto fn = [fd, this](uint32_t events) -> void { onSocketEvent(events, fd); };
    event_ = SocketEventPtr(new SocketEvent(base, fd, fn, SocketEventType::Read|SocketEventType::Write));
}

void ServerConnection::onSocketEvent(uint32_t events, int fd) {
    if (fd < 0) {
        std::cout << "invalid fd\n";
        return;
    }

    if (events & SocketEventType::Closed) {
        std::cout << "closed\n";
        return;
    }

    if (events & SocketEventType::Read) {
        onSocketRead();
    }

    if (events & SocketEventType::Write) {
        onSocketWrite();
    }
}

void ServerConnection::onSocketRead(){
    std::cout << "[onSocketRead]\n";
    uint64_t rc = readData();
}

uint64_t ServerConnection::readData(){
    uint64_t bytes_read = 0;

    while(true) {
        int rc = buffer_.read(fd_, 65535);

        if (rc == 0) {
            puts("finish!");
            break;
        } else if (rc < 0){
            puts("failed?");
            break;
            // exit(1);
        } else {
            bytes_read += rc;
        }
    }

    return bytes_read;
}

void ServerConnection::onSocketWrite(){
    std::cout << "[onSocketWrite]\n";
}

int main(int argc, char **argv) {
    event_base* base { event_base_new() };

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(0); // 0.0.0.0
    sin.sin_port = htons(3000);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(fd, F_SETFL, O_NONBLOCK); // macos does not have SOCK_NONBLOCK
    ::bind(fd, reinterpret_cast<const sockaddr*>(&sin), sizeof(sin));

    int on = 1;
    evconnlistener* listener;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))<0) {
        goto err;
    }

    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof(on))<0) {
        goto err;
    }

    listener = evconnlistener_new(base, accept_conn_cb, NULL, LEV_OPT_CLOSE_ON_FREE, -1, fd);

    if (!listener) {
        perror("Couldn't create listener");
        return 1;
    }
    evconnlistener_set_error_cb(listener, accept_error_cb);

    event_base_loop(base, 0);
    return 0;

 err:
    std::cout << "error\n";
    evutil_closesocket(fd);
    return 1;

}
