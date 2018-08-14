#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <map>

#include "nghttp2/nghttp2.h"

namespace http2 {
    namespace headers {
        static const std::string AUTHORITY = "authority";
        static const std::string CONTENT_TYPE = "content-type";
        static const std::string GRPC_ENCODING = "grpc-encoding";
        static const std::string GRPC_STATUS = "grpc-status";
        static const std::string GRPC_TIMEOUT = "grpc-timeout";
        static const std::string HTTP_STATUS = ":status";
        static const std::string PATH = ":path";
        static const std::string METHOD = ":method";
        static const std::string SCHEME = ":scheme";

        static const std::string CONTENT_TYPE_VALUE = "application/grpc+proto";
    }

    nghttp2_nv make_nghttp2_nv(const std::string &name, const std::string &value, bool noIndex);

    using HeaderMap = std::map<std::string, std::string>;

    std::vector<nghttp2_nv> makeHeaderNv(const HeaderMap &headers);
}
