#include "server.hpp"

namespace http2 {
    const Http2Callbacks callbacks {};

    static ssize_t onSendCallback(nghttp2_session*, const uint8_t* data, size_t length, int, void* user_data) {
        return static_cast<ServerConnection*>(user_data)->onSendCallback(data, length);
    }

    static int onBeginHeaderCallback(nghttp2_session* session, const nghttp2_frame *frame, void *user_data) {
        return static_cast<ServerConnection*>(user_data)->onBeginHeaderCallback(session, frame);
    }

    static int onDataChunkRecvCallback(nghttp2_session*, uint8_t, int32_t stream_id, const uint8_t* data, size_t len, void* user_data) {
        return static_cast<ServerConnection*>(user_data)->onDataChunkRecvCallback(stream_id, data, len);
    }

    static int onFrameRecvCallback(nghttp2_session*, const nghttp2_frame* frame, void* user_data) {
        return static_cast<ServerConnection*>(user_data)->onFrameRecvCallback(frame);
    }

    static int onHeaderCallback(nghttp2_session*, const nghttp2_frame* frame, const uint8_t* raw_name, size_t name_length, const uint8_t* raw_value, size_t value_length, uint8_t, void* user_data) {
        std::string name { raw_name, raw_name+name_length };
        std::string value { raw_value, raw_value+value_length };
        return static_cast<ServerConnection*>(user_data)->onHeaderCallback(frame, std::move(name), std::move(value));
    }

    Http2Callbacks::Http2Callbacks() {
        nghttp2_session_callbacks_new(&callbacks_);

        // nghttp2_session_callbacks_set_on_frame_send_callback(callbacks_, onFrameSendCallback)

        nghttp2_session_callbacks_set_send_callback(callbacks_, onSendCallback);

        nghttp2_session_callbacks_set_on_begin_headers_callback(callbacks_, onBeginHeaderCallback);

        nghttp2_session_callbacks_set_on_data_chunk_recv_callback(callbacks_, onDataChunkRecvCallback);

        nghttp2_session_callbacks_set_on_frame_recv_callback(callbacks_, onFrameRecvCallback);

        nghttp2_session_callbacks_set_on_header_callback(callbacks_, onHeaderCallback)
    }

}
