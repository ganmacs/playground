
#include "session.hpp"

namespace http2 {
    static Http2CallbacksBuilder cb_builder {};

    // static
    Session Session::buildClientSession(ConnectionHandler *handler) {
        Session s {};
        nghttp2_session_client_new(&s.session_, cb_builder.build(), (void *)handler);
        s.bootstrap();
        return s;
    }

    // static
    Session Session::buildServerSession(ConnectionHandler *handler) {
        Session s {};
        nghttp2_session_server_new(&s.session_, cb_builder.build(), (void *)handler);
        s.bootstrap();
        return s;
    }

    // TODO: make callback like method
    // this is grpc logic...
    static ssize_t send_data_with_trailer(nghttp2_session *session, int32_t stream_id,
                                      uint8_t *buf, size_t length,
                                      uint32_t *data_flags,
                                      nghttp2_data_source *source,
                                      void *user_data) {
        SPDLOG_TRACE(logger, "send data with trailer {} bytes fd={}", stream_id, length);

        buffer::BufferWriter* data = (buffer::BufferWriter*)source->ptr;
        size_t a = data->write_to(buf);
        if (a == 0) {
            // send trailers
            *data_flags |= NGHTTP2_DATA_FLAG_NO_END_STREAM;

            // trailers
            HeaderMap hd = { {http2::headers::GRPC_STATUS, "0"} };
            auto nvs = http2::makeHeaderNv(hd);
            int rv  = nghttp2_submit_trailer(session, stream_id, nvs.data(), 1);
            if (rv != 0) {
                logger->error("sending error: %s", nghttp2_strerror(rv));
            }
            return 0;
        } else {
            return a;
        }
    }

    Session::Session() {}

    int Session::bootstrap() {
        int rv = nghttp2_submit_settings(session_, NGHTTP2_FLAG_NONE, 0, 0);
        if (rv != 0) {
            logger->error("Fatal error bootstap: %s", nghttp2_strerror(rv));
            return -1;
        }

        return 0;
    }

    ssize_t Session::processData(const uint8_t *data, size_t len) {
        ssize_t rv = nghttp2_session_mem_recv(session_, data, len);
        if (rv != len) {
            logger->error("Fatal error nghttp2_session_mem_recv: {}", nghttp2_strerror(rv));
            return -1;
        }
        return rv;
    }

    ssize_t Session::sendData() {
        SPDLOG_TRACE(logger, "Start sending reponse data...");

        int rv = nghttp2_session_send(session_);
        if (rv != 0) {
            logger->error("sending packed failed: {}", nghttp2_strerror(rv));
            return -1;
        }
        return 0;
    }

    void Session::registerStream(int32_t stream_id, Stream *stream) {
        int rv = nghttp2_session_set_stream_user_data(session_, stream_id, stream);
        if (rv != 0) {
            logger->error("register stream failed: {}", nghttp2_strerror(rv));
        }
    }

    Stream *Session::getStream(int32_t stream_id) {
        auto user_data = nghttp2_session_get_stream_user_data(session_, stream_id);
        return static_cast<Stream*>(user_data);
    }

    ssize_t Session::submitRequest(DataFrame &d) {
        nghttp2_data_provider data_prd;
        data_prd.source.ptr = d.data_;
        data_prd.read_callback = send_data_with_trailer;

        auto nvs = http2::makeHeaderNv(d.hdrs_);
        auto stream_id = nghttp2_submit_request(session_, nullptr, nvs.data(), d.hdrs_.size(), &data_prd, nullptr);
        if (stream_id < 0) {
            logger->error("Submit request failed: {} {}", stream_id, nghttp2_strerror(stream_id));
            return stream_id;
        }

        return stream_id;
    }

    ssize_t Session::submitResponse(DataFrame &d) {
        nghttp2_data_provider data_prd;
        data_prd.source.ptr = d.data_;
        data_prd.read_callback = send_data_with_trailer;

        auto nvs = http2::makeHeaderNv(d.hdrs_);
        auto rv = nghttp2_submit_response(session_, d.stream_id_, nvs.data(), d.hdrs_.size(), &data_prd);
        if (rv != 0) {
            logger->error("Submit response failed: {}", nghttp2_strerror(rv));
            return rv;
        }
        return 0;
    }

    static ssize_t onSendCallback(nghttp2_session*, const uint8_t* data, size_t length, int, void* user_data) {
        return static_cast<ConnectionHandler*>(user_data)->onSendCallback(data, length);
    }

    static int onBeginHeaderCallback(nghttp2_session* session, const nghttp2_frame *frame, void *user_data) {
        return static_cast<ConnectionHandler*>(user_data)->onBeginHeaderCallback(session, frame);
    }

    static int onDataChunkRecvCallback(nghttp2_session*, uint8_t, int32_t stream_id, const uint8_t* data, size_t len, void* user_data) {
        return static_cast<ConnectionHandler*>(user_data)->onDataChunkRecvCallback(stream_id, data, len);
    }

    static int onFrameRecvCallback(nghttp2_session*, const nghttp2_frame* frame, void* user_data) {
        return static_cast<ConnectionHandler*>(user_data)->onFrameRecvCallback(frame);
    }

    static int onHeaderCallback(nghttp2_session*, const nghttp2_frame* frame, const uint8_t* raw_name, size_t name_length, const uint8_t* raw_value, size_t value_length, uint8_t, void* user_data) {
        std::string name { raw_name, raw_name+name_length };
        std::string value { raw_value, raw_value+value_length };
        return static_cast<ConnectionHandler*>(user_data)->onHeaderCallback(frame, std::move(name), std::move(value));
    }

    static int onStreamCloseCallback(nghttp2_session*, int32_t stream_id, uint32_t error_code, void* user_data) {
        return static_cast<ConnectionHandler*>(user_data)->onStreamCloseCallback(stream_id, error_code);
    }

    Http2CallbacksBuilder::Http2CallbacksBuilder() {
        nghttp2_session_callbacks_new(&callbacks_);

        // nghttp2_session_callbacks_set_on_frame_send_callback(callbacks_, onFrameSendCallback)

        nghttp2_session_callbacks_set_send_callback(callbacks_, onSendCallback);

        nghttp2_session_callbacks_set_on_begin_headers_callback(callbacks_, onBeginHeaderCallback);

        nghttp2_session_callbacks_set_on_data_chunk_recv_callback(callbacks_, onDataChunkRecvCallback);

        nghttp2_session_callbacks_set_on_frame_recv_callback(callbacks_, onFrameRecvCallback);

        nghttp2_session_callbacks_set_on_header_callback(callbacks_, onHeaderCallback);

        nghttp2_session_callbacks_set_on_stream_close_callback(callbacks_, onStreamCloseCallback);
    }
}
