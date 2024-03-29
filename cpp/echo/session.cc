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


    static ssize_t send_trailer(nghttp2_session *session, uint32_t *data_flags, int32_t stream_id) {
        *data_flags |= NGHTTP2_DATA_FLAG_NO_END_STREAM;

        // trailers
        Headers hd = { {http2::headers::GRPC_STATUS, "0"} };
        auto nvs = http2::makeHeaderNv(hd);
        int rv  = nghttp2_submit_trailer(session, stream_id, nvs.data(), 1);
        if (rv != 0) {
            logger->error("sending error: %s", nghttp2_strerror(rv));
        }
        return rv;
    }

    static ssize_t send_data_with_trailer(nghttp2_session *session, int32_t stream_id,
                                          uint8_t *buf, size_t length,
                                          uint32_t *data_flags,
                                          nghttp2_data_source *source,
                                          void *user_data) {
        SPDLOG_TRACE(logger, "send data  with trailer stream_id={} length={}", stream_id, length);

        auto stream = (Stream *)source->ptr;
        std::list<DataFramePtr>* item_list = &stream->item_list_;
        auto total = 0;
        bool end = false;

        while (!item_list->empty() && !stream->local_end_stream_) {
            auto d = item_list->front();
            buffer::BufferWriter *b = (buffer::BufferWriter *)d->data_;

            auto buffer_size = b->length();
            if (total + buffer_size > length) {
                return total;
            }

            size_t write_size = b->write_to(buf);
            total += write_size;

            auto pop = false;

            if (buffer_size == write_size || write_size == 0) {
                item_list->pop_front();
                pop = true;
            }

            if (pop) {
                if (!stream->first_sent_ && d->end_stream_) {
                    stream->local_end_stream_ = true;
                    stream->first_sent_ = true;
                    send_trailer(session, data_flags, stream_id);
                    return total;
                } else if (!stream->first_sent_) {
                    stream->first_sent_ = true;
                    return total;
                } else if (d->end_stream_) {
                    send_trailer(session, data_flags, stream_id);
                    stream->local_end_stream_ = true;
                    return total;
                }
            }
        }

        if (total > 0) {
            return total;
        } else {
            // stop stream DEFERRED;.
            stream->blocking_ = true;
            return NGHTTP2_ERR_DEFERRED;
        }
    }

    static ssize_t send_data_with_trailer2(nghttp2_session *session, int32_t stream_id,
                                      uint8_t *buf, size_t length,
                                      uint32_t *data_flags,
                                      nghttp2_data_source *source,
                                      void *user_data) {
        SPDLOG_TRACE(logger, "send data with trailer {} bytes fd={}", stream_id, length);

        buffer::BufferWriter* data = (buffer::BufferWriter*)source->ptr;
        size_t a = data->write_to(buf);

        if (a == 0) {
            *data_flags |= NGHTTP2_DATA_FLAG_EOF;
            return 0;
        } else {
            if (a == length) {
                *data_flags |= NGHTTP2_DATA_FLAG_EOF;
                return 0;
            }
            return a;
        }
    }

    Session::Session() {}

    int Session::bootstrap() {
        SPDLOG_TRACE(logger, "sending initianl setting frame");

        nghttp2_settings_entry iv[1] = {{NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS, 100}};

        int rv = nghttp2_submit_settings(session_, NGHTTP2_FLAG_NONE, iv, sizeof(iv)/ sizeof(iv[0]));
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

    ssize_t Session::submitRequest(DataFrame &d, Stream *stream) {
        nghttp2_data_provider data_prd;
        data_prd.source.ptr = d.data_;
        data_prd.read_callback = send_data_with_trailer2;

        auto nvs = http2::makeHeaderNv(d.hdrs_);

        // set stream for get stream
        auto stream_id = nghttp2_submit_request(session_, nullptr, nvs.data(), d.hdrs_.size(), &data_prd, stream);
        stream->stream_id_ = stream_id;
        if (stream_id < 0) {
            logger->error("Submit request failed: {} {}", stream_id, nghttp2_strerror(stream_id));
            return stream_id;
        }

        return stream_id;
    }

    ssize_t Session::writeHeader(DataFramePtr d, Stream *stream) {
        if (d->hdrs_.size() <=  0) {
            return 0;
        }

        auto nvs = http2::makeHeaderNv(d->hdrs_);
        // not END_STREAM
        auto rv = nghttp2_submit_headers(session_, NGHTTP2_FLAG_NONE, d->stream_id_, nullptr, nvs.data(), d->hdrs_.size(), stream);
        if (rv < 0) {
            logger->error("Submit header failed: {} {}", rv, nghttp2_strerror(rv));
            return rv;
        }

        return rv;
    }

    ssize_t Session::resume(int32_t stream_id) {
        auto rv = nghttp2_session_resume_data(session_, stream_id);
        if (rv != 0) {
            logger->error("resume sending data failed: {}", nghttp2_strerror(rv));
            return rv;
        }
        return rv;
    }

    ssize_t Session::writeData2(std::list<DataFramePtr> *list) {
        if (list->empty()) {
            return 0;
        }
        nghttp2_data_provider data_prd;
        data_prd.source.ptr = (void *)list;

        data_prd.read_callback = [](nghttp2_session *session, int32_t stream_id, uint8_t *buf, size_t length, uint32_t *data_flags, nghttp2_data_source *source, void *user_data) -> ssize_t {
            std::list<DataFramePtr>* item_list = (std::list<DataFramePtr> *)source->ptr;
            auto total = 0;
            bool end = false;

            while (!item_list->empty()) {
                auto d = item_list->front();
                buffer::BufferWriter *b = (buffer::BufferWriter *)d->data_;
                // TODO: check total buffer size + buffer size <  length
                size_t size = b->write_to(buf);

                if (size == 0) {
                    item_list->pop_front();

                    if (d->end_stream_) {
                        *data_flags |= NGHTTP2_DATA_FLAG_EOF;
                        return total;
                    }
                }
                total += size;
            }

            if (total > 0) {
                return total;
            } else {
                return NGHTTP2_ERR_DEFERRED;
            }
        };

        // data_prd.read_callback = send_data_with_trailer2;

        auto d = list->front();
        auto rv = nghttp2_submit_data(session_, NGHTTP2_FLAG_END_STREAM, d->stream_id_, &data_prd);
        if (rv != 0) {
            logger->error("Submit data failed: {}", nghttp2_strerror(rv));
            return rv;
        }

        return 0;
    }

    ssize_t Session::submitResponse(DataFramePtr d, Stream *stream) {
        nghttp2_data_provider data_prd;
        auto h_size = d->hdrs_.size();
        auto nvs = http2::makeHeaderNv(d->hdrs_);
        auto stream_id = d->stream_id_;

        data_prd.source.ptr = (void *)stream;
        data_prd.read_callback = send_data_with_trailer;

        stream->item_list_.emplace_front(std::move(d));
        auto rv = nghttp2_submit_response(session_, stream_id, nvs.data(), h_size, &data_prd);
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

    static int onFrameSendCallback(nghttp2_session*, const nghttp2_frame *frame, void *user_data) {
        return static_cast<ConnectionHandler*>(user_data)->onFrameSendCallback(frame);
    }

    static int onHeaderCallback(nghttp2_session*, const nghttp2_frame* frame, const uint8_t* raw_name, size_t name_length, const uint8_t* raw_value, size_t value_length, uint8_t, void* user_data) {
        std::string name { raw_name, raw_name+name_length };
        std::string value { raw_value, raw_value+value_length };
        return static_cast<ConnectionHandler*>(user_data)->onHeaderCallback(frame, std::move(name), std::move(value));
    }

    static int onStreamCloseCallback(nghttp2_session*, int32_t stream_id, uint32_t error_code, void* user_data) {
        return static_cast<ConnectionHandler*>(user_data)->onStreamCloseCallback(stream_id, error_code);
    }

    static int onInvalidFrameRecvCallback(nghttp2_session *session, const nghttp2_frame *frame, int lib_error_code, void *user_data) {
        return static_cast<ConnectionHandler*>(user_data)->onInvalidFrameRecvCallback(frame, lib_error_code);
    }

    Http2CallbacksBuilder::Http2CallbacksBuilder() {
        nghttp2_session_callbacks_new(&callbacks_);

        nghttp2_session_callbacks_set_send_callback(callbacks_, onSendCallback);

        nghttp2_session_callbacks_set_on_begin_headers_callback(callbacks_, onBeginHeaderCallback);

        nghttp2_session_callbacks_set_on_data_chunk_recv_callback(callbacks_, onDataChunkRecvCallback);

        nghttp2_session_callbacks_set_on_frame_recv_callback(callbacks_, onFrameRecvCallback);

        nghttp2_session_callbacks_set_on_frame_send_callback(callbacks_, onFrameSendCallback);

        nghttp2_session_callbacks_set_on_header_callback(callbacks_, onHeaderCallback);

        nghttp2_session_callbacks_set_on_invalid_frame_recv_callback(callbacks_, onInvalidFrameRecvCallback);

        nghttp2_session_callbacks_set_on_stream_close_callback(callbacks_, onStreamCloseCallback);
    }
}
