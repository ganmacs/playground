#pragma once

#include <string>

#include <arpa/inet.h>

#include "network.hpp"

namespace vega {
    namespace network {
        class Ip {
        public:
            Ip(const std::string& addr, const uint32_t port) noexcept;
            sockaddr_in* sockAddr() noexcept;
            int socket(SocketType type) noexcept;
            int bind(int fd) noexcept;
            const std::string& toString() const { return friendly_name_; }

        private:
            int socketFromSocketType(SocketType type) noexcept;

            sockaddr_in address_;
            std::string friendly_name_;
        };

        using IpPtr = std::unique_ptr<Ip>;
    }
}
