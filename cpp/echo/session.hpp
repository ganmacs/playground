#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "nghttp2/nghttp2.h"

#include "connection_handler.hpp"
#include "frame.hpp"
#include "headers.hpp"
#include "stream.hpp"
#include "buffer.hpp"        // XXX
#include "headers.hpp"        // XXX
#include "logger.hpp"

namespace http2 {
    class Server {
    public:
        Server() {};
    };

    class Session {
    public:
        static Session buildClientSession(ConnectionHandler *handler);
        static Session buildServerSession(ConnectionHandler *handler);

        Session();
        ssize_t processData(const uint8_t *data, size_t len);
        ssize_t submitResponse(DataFrame &d);
        ssize_t sendRequest();
        ssize_t sendResponse();
        void registerStream(int32_t stream_id, Stream *stream);
        Stream *getStream(int32_t stream_id);

    private:
        int bootstrap();
        void processControlBuf(const size_t process_size);
        nghttp2_session *session_;
    };

    class Http2CallbacksBuilder {
    public:
        Http2CallbacksBuilder();
        const nghttp2_session_callbacks* build() { return callbacks_; }

    private:
        nghttp2_session_callbacks* callbacks_;
    };
}
