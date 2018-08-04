#include "frame.hpp"

namespace http2 {
    DataFrame::DataFrame(int32_t id, bool end_stream, std::map<std::string, std::string> headers):
        stream_id_{id}, end_stream_{end_stream}, hdrs_{headers} {};

    DataFrame::DataFrame(int32_t id, bool end_stream): DataFrame(id, end_stream, {}) {};

    DataFrame::DataFrame(int32_t id): DataFrame(id, false, {}) {};
}
