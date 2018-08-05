#pragma once

#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <string>
#include <list>
#include <unordered_map>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <memory>
#include <utility>

#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/event.h"
#include "event2/event_struct.h"
#include "nghttp2/nghttp2.h"

#include "hellworld.pb.h"
#include "buffer.hpp"
#include "frame.hpp"
#include "headers.hpp"
#include "server.hpp"

struct RawSlice {
    void* mem_ = nullptr;
    size_t len_ = 0;
};

using SocketEventCb = std::function<void(uint32_t events)>;

// RawSlice is the same structure as evbuffer_iovec. This was put into place to avoid leaking
// libevent into most code since we will likely replace evbuffer with our own implementation at
// some point. However, we can avoid a bunch of copies since the structure is the same.
static_assert(sizeof(RawSlice) == sizeof(evbuffer_iovec), "RawSlice != evbuffer_iovec");
static_assert(offsetof(RawSlice, mem_) == offsetof(evbuffer_iovec, iov_base),
              "RawSlice != evbuffer_iovec");
static_assert(offsetof(RawSlice, len_) == offsetof(evbuffer_iovec, iov_len),
              "RawSlice != evbuffer_iovec");

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

struct SocketEventType {
    static const uint32_t Read = 0x1;
    static const uint32_t Write = 0x2;
    static const uint32_t Closed = 0x4;
};

class  SocketEvent {
public:
    SocketEvent(event_base* base, int fd, SocketEventCb cb, uint32_t events);
    void assignEvents(uint32_t events);

private:
    static void onEventCallback(evutil_socket_t, short what, void* arg);

    event_base* base_;
    SocketEventCb cb_;
    int fd_;
    event raw_event_;
};

using SocketEventPtr = std::unique_ptr<SocketEvent>;

class ServerConnection: public http2::ConnectionHandler {
public:
    // ~ServerConnection() { nghttp2_session_callbacks_del(session_); }
    ServerConnection(event_base* base, evutil_socket_t fd);
    ServerConnection* base() { return this; }
    // void sessionRecv(Buffer& buf);
    // void sendPendingFrames();

    // for libevent2 callbacks
    void onSocketEvent(uint32_t events);

    // for nghttp2 callbacks
    ssize_t onSendCallback(const uint8_t* data, const size_t length);
    int onBeginHeaderCallback(nghttp2_session *session, const nghttp2_frame *frame);
    int onHeaderCallback(const nghttp2_frame *frame, std::string name, std::string value);
    int onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len);
    int onFrameRecvCallback(const nghttp2_frame* frame);
private:
    uint64_t readData();
    void onSocketRead();
    void onSocketWrite();
    // Stream* getStream(int32_t stream_id);

    // int saveHeader(const nghttp2_frame *frame, std::string name, std::string value);

    int fd_;
    Buffer read_buffer_;
    Buffer write_buffer_;
    // nghttp2_session* session_;
    SocketEventPtr event_;
    http2::Session session_;
    // linked list
    std::list<http2::StreamPtr> streams_;
};

using ServerConnectionPtr = std::unique_ptr<ServerConnection>;
