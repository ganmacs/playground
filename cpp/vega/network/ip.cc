#include "ip.hpp"

namespace vega {
    namespace network {
        Ip::Ip(const std::string& addr, const uint32_t port) noexcept {
            memset(&address_, 0, sizeof(address_));

            address_.sin_family = AF_INET;
            address_.sin_port = htons(port);

            const int rc = ::inet_pton(AF_INET, addr.data(), &address_.sin_addr);
            if (1 != rc) {
                logger->error("Invalid addr or port {}:{}", addr, port);
                abort();
            }
        }

        int Ip::bind(int fd) noexcept {
            return ::bind(fd, reinterpret_cast<const sockaddr*>(&address_), sizeof(address_));
        }

        int Ip::socket(SocketType type) noexcept { return socketFromSocketType(type); }

        int Ip::socketFromSocketType(SocketType type) noexcept {
            int flags = 0;
            if (type == SocketType::Stream) {
                flags |= SOCK_STREAM;
            } else {
                flags |= SOCK_DGRAM;
            }

            const int fd = ::socket(AF_INET, flags, 0);
            if (fd == -1) {
                logger->error("Opening socket faied: {}", strerror(errno));
                return -1;
            }

            const int rv = fcntl(fd, F_SETFL, O_NONBLOCK); // macos does not have SOCK_NONBLOCK
            if (rv == -1) {
                logger->error("Making socket nonblock failed: {}", strerror(errno));
                return -1;
            }

            return fd;
        }
    }
}
