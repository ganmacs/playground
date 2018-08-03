#include "frame.hpp"

namespace http2 {
    DataFrame::DataFrame(uint32_t id, bool end_stream): DataFrame(id) { end_stream_ = end_stream; };
}
