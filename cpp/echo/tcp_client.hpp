#pragma once

#include <string>
#include <list>

#include "event2/event.h"
#include "nghttp2/nghttp2.h"

#include "hellworld.pb.h"

#include "logger.hpp"
#include "socket.hpp"
#include "socket_event.hpp"
#include "session.hpp"
#include "connection_handler.hpp"

class ClientConnection: public http2::ConnectionHandler {
public:
    static ClientConnection connect(event_base* base, const std::string host, const uint port);
    ClientConnection(event_base* base, Network::SocketPtr socket);
    ClientConnection* base() { return this; }
    int fd() { return socket_.get()->fd(); }
    void request();

    void onSocketEvent(uint32_t events);
    void onSocketRead();
    void onSocketWrite();

    // For ConnectionHandler
    ssize_t onSendCallback(const uint8_t *data, size_t length) override;
    int onBeginHeaderCallback(nghttp2_session* session, const nghttp2_frame *frame) override;
    int onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len) override;
    int onFrameRecvCallback(const nghttp2_frame* frame) override;
    int onHeaderCallback(const nghttp2_frame* frame, std::string name, std::string value) override;
    int onStreamCloseCallback(int32_t stream_id, uint32_t error_code) override;

private:
    event_base *base_;
    Network::BufferedSocketPtr socket_;
    Event::SocketEventPtr socket_event_;
    std::list<http2::StreamPtr> streams_;

    // make unique ptr
    http2::Session session_;
};

namespace Tcp {}
