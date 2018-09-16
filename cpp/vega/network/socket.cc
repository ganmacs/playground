#include "socket.hpp"

namespace vega {
    namespace network {
        Socket::Socket(Ip ip): ip_(ip) {}

        Socket::~Socket() {
            ::close(fd_);
        }

        const int Socket::connect() noexcept {
            return ::connect(fd_, reinterpret_cast<const sockaddr*>(ip_.sockAddr()), sizeof(struct sockaddr));
        }

        const int Socket::request(std::string msg) noexcept {
            return ::write(fd_, (void *)msg.data(), msg.length());
        }

        const int Socket::openSocket(SocketType type) noexcept {
            int flags = 0;
            if (type == SocketType::Stream) {
                flags |= SOCK_STREAM;
            } else {
                flags |= SOCK_DGRAM;
            }

            int fd = socket(AF_INET, flags, 0);
            if (fd == -1) {
                logger->error("Opening socket faied: {}", strerror(errno));
                return -1;
            }

            int rv = fcntl(fd, F_SETFL, O_NONBLOCK); // macos does not have SOCK_NONBLOCK
            if (rv == -1) {
                logger->error("Making socket nonblock failed: {}", strerror(errno));
                return -1;
            }

            return fd;
        }

        const int Socket::openListenerSocket() noexcept {
            int fd = openSocket(SocketType::Stream);
            if (fd == -1) {
                return -1;
            }

            int on = 1;
            int rc = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
            if (rc) {
                logger->error("setsockopt returns", strerror(errno));
                return -1;
            }

            fd_ = fd;
            return fd;
        }
    }
}
