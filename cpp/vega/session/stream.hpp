#pragma once

#include "memory"

namespace vega {
    namespace session {
        class Stream {
        public:
            Stream(const uint32_t stream_id);

        private:
            const uint32_t stream_id_;
        };
        using StreamPtr = std::shared_ptr<Stream>;
    }
}
