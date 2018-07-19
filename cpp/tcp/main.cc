#include "event2/listener.h"
#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/event.h"
#include <iostream>
#include <algorithm>
#include <string>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

struct event_base;
extern "C" {
    void event_base_free(event_base*);
}

namespace Libevent {
    typedef event_base EventBase;
}

// typedef CSmartPtr<event_base, event_base_free> BasePtr;
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


static void dummyHttp(int fd)  {
    std::string header {"HTTP1.1 200 OK\nContent-Type: text/plain\n\nbody"};
    ::write(fd, header.c_str(), header.size());
}

class Socket {
public:
    Socket(int fd): fd_{fd} {}

    int fd() { return fd_; }
    void close() { ::close(fd_); }

private:
    const int fd_;
};

class Buffer {
public:
    Buffer(): buffer_{evbuffer_new()} {}
    // ~Buffer() { evbuffer_free(buffer_); }

    int read(const int fd, const uint64_t max_length) {
        puts("-- read! --");
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

    void commit(RawSlice* iovecs, uint64_t const size) {
        int ret = evbuffer_commit_space(buffer_, reinterpret_cast<evbuffer_iovec*>(iovecs), size);
        if (ret != 0) {
            puts("evbuffer_commit_sapce failed");
            exit(1);
        }
    }

    uint64_t getAvailableSliceCount()  {
        return getRawSlice(nullptr, 0);
    }
    uint64_t getRawSlice(RawSlice* out, uint64_t size)  {
        return evbuffer_peek(buffer_, -1, nullptr, reinterpret_cast<evbuffer_iovec*>(out), size);
    }

    evbuffer* buffer() { return buffer_; }
private:
    uint64_t reserve(uint64_t const length, RawSlice* iovecs, uint64_t const iovecs_num) {
        int ret = evbuffer_reserve_space(buffer_, length, reinterpret_cast<evbuffer_iovec*>(iovecs), iovecs_num);
        if (ret < 0) {
            printf("%d\n", ret);
            exit(1);
        }
        return ret;
    }

    evbuffer* buffer_;
};

class Connection {
public:
    Connection(): buffer_{} {}
    Buffer* buffer() { return &buffer_; }
private:
    // int fd_;
    Buffer buffer_;
};

class Server {
public:
    static void listenCallback(evconnlistener*, evutil_socket_t fd, sockaddr* remote_addr, int remote_addr_len, void* arg);

    Server(int fd): base_{ event_base_new() }, s_{fd} {
        int on = 1;
        int rc = setsockopt(s_.fd(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (rc) {
            s_.close();
            printf( "rc is -1\n");
        }
    }

    int setup(int port) {
        if (bind(port)< 0) {
            printf("failed binding\n");
            return -1;
        }
        evconnlistener_new(base_, listenCallback, this, 0, -1, s_.fd());
        return 1;
    }

    void start() {
        event_base_loop(base_, 0);
    }

    int fd() { return s_.fd(); }
private:
    Libevent::EventBase* base_;
    Socket s_;

    int bind(int port) {
        sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(0);
        addr.sin_port = htons(port);

        return ::bind(s_.fd(), reinterpret_cast<const sockaddr*>(&addr), sizeof(addr));
    }
};


void Server::listenCallback(evconnlistener*, evutil_socket_t fd, sockaddr* remote_addr, int remote_addr_len, void* arg) {
    Server* server = static_cast<Server*>(arg);
    printf("received %d %d\n", fd, server->fd());
    Connection conn {};

    uint64_t bytes_read = 0;
    while(true) {
        int rc = conn.buffer()->read(fd, 65535);

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

    uint64_t size = conn.buffer()->getAvailableSliceCount();
    RawSlice slices[size];
    conn.buffer()->getRawSlice(slices, size);

    for (auto s : slices) {
        char* v = static_cast<char*>(s.mem_);
        printf("%s\n", v);
    }

    dummyHttp(fd);
    close(fd);
}



int main(int argc, char *argv[])
{
    Server s { socket(AF_INET, SOCK_STREAM, 0) };
    if (s.setup(3000) < 0) {
        printf("failed" );
    }
    s.start();
    return 0;
}
