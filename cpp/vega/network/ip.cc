#include "ip.hpp"

namespace vega {
    namespace network {
        Ip::Ip(const std::string& addr, const uint32_t port) noexcept {
            memset(&address_, 0, sizeof(address_));

            address_.sin_family = AF_INET;
            address_.sin_port = htons(port);
            int rc = ::inet_pton(AF_INET, addr.data(), &address_.sin_addr);

            if (1 != rc) {
                logger->error("Invalid addr or port {}:{}", addr, port);
                abort();
            }
        }

        const sockaddr_in* Ip::sockAddr() noexcept {
            return &address_;
        }
    }
}
