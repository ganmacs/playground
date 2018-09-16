#include "socket.hpp"

namespace network {
    Socket::Socket(const std::string host, const uint port) {
        memset(&address_, 0, sizeof(address_));

        address_.sin_family = AF_INET;
        address_.sin_port = htons(port);
        int rc = ::inet_pton(AF_INET, host.data(), &address_.sin_addr);

        if (1 != rc) {
            throw "errro\n";
        }

        fd_ = socket(AF_INET, SOCK_STREAM, 0);
        fcntl(fd_, F_SETFL, O_NONBLOCK); // macos does not have SOCK_NONBLOCK
    }

    Socket::~Socket() {
        ::close(fd_);
    }

    const int Socket::connect() noexcept {
        return ::connect(fd_, reinterpret_cast<const sockaddr*>(&address_), sizeof(struct sockaddr));
    }

    const int Socket::request(std::string msg) noexcept {
        return ::write(fd_, (void *)msg.data(), msg.length());
    }

}
