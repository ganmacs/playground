#include "socket.hpp"

namespace vega {
    namespace network {
        BaseSocket::BaseSocket(int fd, IpPtr ip): fd_{fd}, ip_{std::move(ip)} {}

        BaseSocket::~BaseSocket() {
            ::close(fd_);
        }

        int BaseSocket::doBind() noexcept {
            return ip_.get()->bind(fd_);
        }

        // const int Socket::connect() noexcept {
        //     return ::connect(fd_, reinterpret_cast<const sockaddr*>(ip_.get()->sockAddr()), sizeof(struct sockaddr));
        // }

        // const int Socket::write(const std::string& msg) noexcept {
        //     return ::write(fd_, (void *)msg.data(), msg.length());
        // }

        TcpListenSocket::TcpListenSocket(const std::string addr, const uint32_t port)
            : TcpListenSocket(std::make_unique<vega::network::Ip>(addr, port)) {}


        TcpListenSocket::TcpListenSocket(IpPtr ip)
            : base_socket(std::make_unique<BaseSocket>(ip->socket(SocketType::Stream), std::move(ip)))
        {

            if (fd() == -1) {
                logger->error("fd is invalid");
                abort();
            }

            const int on = 1;
            const int rc = setsockopt(fd(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
            if (rc == -1) {
                logger->error("setsockopt returns {}", strerror(errno));
                abort();
            }
        }
    }
}
