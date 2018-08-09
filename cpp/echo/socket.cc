#include "socket.hpp"

namespace Network {
    Socket::Socket(SocketType t): fd_{ buildListerSocket() } {
        memset(&address_, 0, sizeof(address_));
    };

    Socket::Socket(): Socket(SocketType::Stream) {};

    void Socket::close() { ::close(fd_); }

    const int Socket::bind(const std::string host, const uint port) {
        int rv;
        rv = sockaddrIn(host, port);
        if (rv < 0) {
            return rv;
        }

        rv = ::bind(fd_, reinterpret_cast<const sockaddr*>(&address_), sizeof(address_));
        if (rv < 0) {
            logger->error("bind call failed: {}", strerror(errno));
            return rv;
        }

        return 0;
    }

    void Socket::connect() {  }

    // only ipv4 support
    const int Socket::sockaddrIn(const std::string host, const uint port) {
        address_.sin_family = AF_INET;
        address_.sin_port = htons(port);
        int rc = ::inet_pton(AF_INET, host.data(), &address_.sin_addr);
        if (1 != rc) {
            logger->error("Invalid ipv4 address '{}'", host);
            return -1;
        }
        return 0;
    };
}
