#include <string>

#include <arpa/inet.h>

#include "../logger.hpp"

namespace vega {
    namespace network {
        class Ip {
        public:
            Ip(const std::string& addr, const uint32_t port) noexcept;
            const sockaddr_in* sockAddr() noexcept;

        private:
            sockaddr_in address_;
        };
    }
}
