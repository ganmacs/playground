#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>

#include "nghttp2/nghttp2.h"

#include "connection_handler.hpp"
#include "frame.hpp"
#include "headers.hpp"
#include "stream.hpp"
#include "buffer.hpp"        // XXX
#include "headers.hpp"        // XXX
#include "logger.hpp"

namespace http2 {
    class Stream;

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
        ssize_t submitRequest(DataFrame &d, Stream *stream);

        ssize_t sendData();
        void registerStream(int32_t stream_id, Stream *stream);
        Stream *getStream(int32_t stream_id);

        ssize_t writeHeader(DataFramePtr d, Stream *stream);
        ssize_t writeData(DataFrame &d);
        ssize_t writeData2(std::list<DataFramePtr> *list);
        ssize_t resume(int32_t stream_id);

        // ssize_t sendMsg(DataFrame &d, Stream *stream);
        // ssize_t sendCloseMsg(DataFrame &d);
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
