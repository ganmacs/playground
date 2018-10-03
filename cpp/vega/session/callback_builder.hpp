#pragma once

#include <nghttp2/nghttp2.h>

#include "session_handler.hpp"

namespace vega {
    namespace session {
        class Http2CallbacksBuilder {
        public:
            Http2CallbacksBuilder() {
                nghttp2_session_callbacks_new(&callbacks_);

                nghttp2_session_callbacks_set_send_callback(callbacks_, [](nghttp2_session*, const uint8_t* data, size_t length, int, void* user_data) -> ssize_t {
                        return static_cast<SessionHandler*>(user_data)->onSendCallback(data, length);
                    });

                nghttp2_session_callbacks_set_on_begin_headers_callback(callbacks_, [](nghttp2_session* session, const nghttp2_frame *frame, void *user_data) -> int {
                        return static_cast<SessionHandler*>(user_data)->onBeginHeaderCallback(session, frame);
                    });

                nghttp2_session_callbacks_set_on_data_chunk_recv_callback(callbacks_, [](nghttp2_session*, uint8_t, int32_t stream_id, const uint8_t* data, size_t len, void* user_data) -> int{
                        return static_cast<SessionHandler*>(user_data)->onDataChunkRecvCallback(stream_id, data, len);
                    });

                nghttp2_session_callbacks_set_on_frame_recv_callback(callbacks_, [](nghttp2_session*, const nghttp2_frame* frame, void* user_data) -> int {
                        return static_cast<SessionHandler*>(user_data)->onFrameRecvCallback(frame);
                    });

                nghttp2_session_callbacks_set_on_frame_send_callback(callbacks_, [](nghttp2_session*, const nghttp2_frame *frame, void *user_data) -> int {
                        return static_cast<SessionHandler*>(user_data)->onFrameSendCallback(frame);
                    });

                nghttp2_session_callbacks_set_on_header_callback(callbacks_, [](nghttp2_session*, const nghttp2_frame* frame, const uint8_t* raw_name, size_t name_length, const uint8_t* raw_value, size_t value_length, uint8_t, void* user_data) -> int {
                        return static_cast<SessionHandler*>(user_data)->onHeaderCallback(frame, std::string { raw_name, raw_name+name_length }, std::string { raw_value, raw_value+value_length });
                    });

                nghttp2_session_callbacks_set_on_stream_close_callback(callbacks_, [](nghttp2_session*, int32_t stream_id, uint32_t error_code, void* user_data) -> int{
                        return static_cast<SessionHandler*>(user_data)->onStreamCloseCallback(stream_id, error_code);
                    });

                // nghttp2_session_callbacks_set_on_invalid_frame_recv_callback(callbacks_, [](nghttp2_session *session, const nghttp2_frame *frame, int lib_error_code, void *user_data) -> int {
                //         return static_cast<SessionHandler*>(user_data)->onInvalidFrameRecvCallback(frame, lib_error_code);
                //     });
            };

            constexpr nghttp2_session_callbacks* build() { return callbacks_; }

        private:
            nghttp2_session_callbacks* callbacks_;
        };


        static Http2CallbacksBuilder callback_builder {};
    }
}
