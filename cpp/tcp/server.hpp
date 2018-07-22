#pragma once

#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <string>

#include "event2/listener.h"
#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/event.h"

#include "nghttp2/nghttp2.h"

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

class Socket {
public:
    Socket(int fd): fd_{fd} {}

    int fd() { return fd_; }
    void close() { ::close(fd_); }

private:
    const int fd_;
};

class Server {
public:
    Server(int fd);

    int setup(int port);

    void start() {
        std::cout << "Server starting...\n";
        event_base_loop(base_, 0);
    }

    int fd() { return s_.fd(); }

    Libevent::EventBase* eventBase() { return base_; }

    static void listenCallback(evconnlistener*, evutil_socket_t fd, sockaddr* remote_addr, int remote_addr_len, void* arg);
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
private:
    uint64_t reserve(uint64_t const length, RawSlice* iovecs, uint64_t const iovecs_num);
    evbuffer* buffer_;
};

namespace Network {
    class Connection {
    public:
        Connection(): buffer_{} {}
        Buffer& buffer() { return buffer_; }

        void write(Buffer& buf) {
            std::cout << "[write]";
        }
    private:
        // int fd_;
        Buffer buffer_;
    };
}

class Http2Callbacks {
public:
    Http2Callbacks();
    // ~Http2Callbacks();

    const nghttp2_session_callbacks* callbacks() { return callbacks_; }
private:
    nghttp2_session_callbacks* callbacks_;
};

class Connection {
public:
    virtual ssize_t onSendCallback(const uint8_t* data, const size_t length) = 0;
};

class ServerConnection: public Connection {
public:
    // ~ServerConnection() { nghttp2_session_callbacks_del(session_); }
    ServerConnection(Server* server, evutil_socket_t fd);
    Connection* base() { return this; }
    void sessionRecv(Buffer& buf);
    void sendPendingFrames();
    void read(bufferevent *bev);

    ssize_t onSendCallback(const uint8_t* data, const size_t length);

    static void readCallback(bufferevent *bev, void *ptr) {
        std::cout << "[readCallback] invoked\n";
        ServerConnection *conn = static_cast<ServerConnection *>(ptr);
        conn->read(bev);
    }

    static void writeCallback(bufferevent *bev, void *ptr) {
        std::cout << "[writeCallback] invoked\n";
        ServerConnection *conn = static_cast<ServerConnection *>(ptr);

    }

    static void eventCallback(bufferevent *bev, short events, void *ptr) {
        std::cout << "[eventCallback] invoked\n";
        ServerConnection *conn = static_cast<ServerConnection *>(ptr);
    }

private:
    bufferevent* bufferevent_;
    Network::Connection connection_ {};
    nghttp2_session* session_;
};
