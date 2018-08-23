#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <map>

#include "nghttp2/nghttp2.h"

namespace http2 {
    namespace headers {
        static const std::string METHOD = ":method";
        static const std::string SCHEME = ":scheme";
        static const std::string PATH = ":path";
        static const std::string AUTHORITY = ":authority";
        static const std::string TE = "te";
        static const std::string GRPC_TIMEOUT = "grpc-timeout";
        static const std::string CONTENT_TYPE = "content-type";
        static const std::string IDENTITY = "identity";
        static const std::string GRPC_ENCODING = "grpc-encoding";
        static const std::string GRPC_ACCEPT_ENCODING = "grpc-accept-encoding";
        static const std::string USER_AGENT = "user-agentn";
        static const std::string GRPC_MESSAGE_TYPE = "grpc-message-type";

        static const std::string HTTP_STATUS = ":status";
        static const std::string GRPC_STATUS = "grpc-status";
        static const std::string GRPC_MESSAGE = "grpc-message";

        static const std::string POST = "POST";
        static const std::string HTTP = "http";
        static const std::string HTTPS = "https";
        static const std::string UA_VALUE = "grpc-ruby-ruby/0.0.1 (by c++)";

        static const std::string CONTENT_TYPE_VALUE = "application/grpc";
        static const std::string TE_VALUE = "trailers";
    }

    nghttp2_nv make_nghttp2_nv(const std::string &name, const std::string &value, bool noIndex);

    using HeaderMap = std::map<std::string, std::string>;

    std::vector<nghttp2_nv> makeHeaderNv(const HeaderMap &headers);
}
