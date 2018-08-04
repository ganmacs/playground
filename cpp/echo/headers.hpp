#pragma once

#include <cstdint>
#include <string>

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
        static const std::string SCHEMA = ":schema";

        static const std::string CONTENT_TYPE_VALUE = "application/grpc";
    }
}
