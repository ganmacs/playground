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

class Buffer {
public:
    Buffer(): buffer_{evbuffer_new()} {}
    Buffer(const void* data, const uint64_t length): Buffer {} {
        add(data, length);
    }
    // ~Buffer() { evbuffer_free(buffer_); }

    int add(const void* data, uint64_t size);
    int write(const int fd);
    int read(const int fd, const uint64_t max_length);

    void drain(const uint64_t len);
    void commit(RawSlice* iovecs, uint64_t const size) {
        int ret = evbuffer_commit_space(buffer_, reinterpret_cast<evbuffer_iovec*>(iovecs), size);
        if (ret != 0) {
            puts("evbuffer_commit_sapce failed");
            exit(1);
        }
    }

    uint64_t getAvailableSliceCount()  { return getRawSlice(nullptr, 0); }
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
        Buffer* buffer() { return &buffer_; }

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
    ServerConnection(Network::Connection conn);
    ssize_t onSendCallback(const uint8_t* data, const size_t length);
    Connection* base() { return this; }
private:
    nghttp2_session* session_;
    Network::Connection connection_;
};
