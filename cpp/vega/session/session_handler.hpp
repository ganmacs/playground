#pragma once

#include <nghttp2/nghttp2.h>
#include <string>

namespace vega {
    namespace session {
        class SessionHandler {
        public:
            virtual ~SessionHandler() {};
            virtual ssize_t onSendCallback(const uint8_t *data, size_t length) = 0;
            virtual int onBeginHeaderCallback(nghttp2_session* session, const nghttp2_frame *frame) = 0;
            virtual int onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len) = 0;
            virtual int onFrameRecvCallback(const nghttp2_frame* frame) = 0;
            virtual int onFrameSendCallback(const nghttp2_frame* frame) = 0;
            virtual int onHeaderCallback(const nghttp2_frame* frame, std::string name, std::string value) = 0;
            virtual int onStreamCloseCallback(int32_t stream_id, uint32_t error_code) = 0;
            // virtual int onInvalidFrameRecvCallback(const nghttp2_frame *frame, int error_code) {
            //     return 0;
            // };
        };
    }
}
