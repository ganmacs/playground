#pragma once

#include <cstdint>
#include <string>

#include "nghttp2/nghttp2.h"

namespace http2 {
    class ConnectionHandler {
    public:
        virtual ssize_t onSendCallback(const uint8_t *data, size_t length) = 0;
        virtual int onBeginHeaderCallback(nghttp2_session* session, const nghttp2_frame *frame) = 0;
        virtual int onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len) = 0;
        virtual int onFrameRecvCallback(const nghttp2_frame* frame) = 0;
        virtual int onHeaderCallback(const nghttp2_frame* frame, std::string name, std::string value) = 0;
    };
}
