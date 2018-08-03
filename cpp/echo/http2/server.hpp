#pragma once

#include <cstdint>
#include <string>

#include "nghttp2/nghttp2.h"

namespace http2 {
    class Server {
    public:
        Server() {};
    };

    class Http2Callbacks {
    public:
        Http2Callbacks();
        const nghttp2_session_callbacks* callbacks() { return callbacks_; }

    private:
        nghttp2_session_callbacks* callbacks_;
    };
}
