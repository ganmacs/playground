#pragma once

#include <cstdint>

namespace http2 {
    namespace headers {
        const uint8_t AUTHORITY[] = "authority";
        const uint8_t CONTENT_TYPE[] = "content-type";
        const uint8_t GRPC_ENCODING[] = "grpc-encoding";
        const uint8_t GRPC_STATUS[] = "grpc-status";
        const uint8_t GRPC_TIMEOUT[] = "grpc-timeout";
        const uint8_t HTTP_STATUS[] = ":status";
        const uint8_t PATH[] = ":path";
        const uint8_t METHOD[] = ":method";
        const uint8_t SCHEMA[] = ":schema";

        // const uint8_t CONTENT_TYPE_VALUE[] = "application/grpc";
    }
}
