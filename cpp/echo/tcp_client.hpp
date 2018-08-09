#pragma once

#include "string"

#include "event2/event.h"
#include "nghttp2/nghttp2.h"

#include "logger.hpp"
#include "socket.hpp"
#include "connection_handler.hpp"

class ClientConnection: public http2::ConnectionHandler {
public:
    ClientConnection(event_base* base, Network::SocketPtr socket);

    // For ConnectionHandler
    ssize_t onSendCallback(const uint8_t *data, size_t length) override;
    int onBeginHeaderCallback(nghttp2_session* session, const nghttp2_frame *frame) override;
    int onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len) override;
    int onFrameRecvCallback(const nghttp2_frame* frame) override;
    int onHeaderCallback(const nghttp2_frame* frame, std::string name, std::string value) override;
    int onStreamCloseCallback(int32_t stream_id, uint32_t error_code) override;

private:
    Network::SocketPtr socket_;
};

namespace Tcp {}
