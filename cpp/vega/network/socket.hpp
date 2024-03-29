#pragma once

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include "network.hpp"
#include "ip.hpp"
#include "../logger.hpp"

namespace vega {
    namespace network {
        class BaseSocket {
        public:
            BaseSocket(int fd, IpPtr ip);
            ~BaseSocket();

            int fd() noexcept { return fd_; }
            // const int connect() noexcept;
            // const int write(const std::string& msg) noexcept;
            int doBind() noexcept;
            // const int openSocket(SocketType type) noexcept;
            int openListenerSocket() noexcept;
            const std::string& toString() const { return ip_->toString(); }

        private:
            const int fd_;
            const IpPtr ip_;
        };
        using BaseSocketPtr = std::unique_ptr<BaseSocket>;

        class TcpListenSocket {
        public:
            explicit TcpListenSocket(IpPtr ip);
            explicit TcpListenSocket(const std::string host, const uint32_t port);

            int fd() noexcept { return base_socket->fd(); }
            int doBind() noexcept { return base_socket->doBind(); }
            int doListen(int backlog) noexcept;
            const std::string& toString() const { return base_socket->toString(); }

        private:
            BaseSocketPtr base_socket;
        };

        using TcpListenSocketPtr = std::unique_ptr<TcpListenSocket>;

        class AcceptedSocket {
        public:
            explicit AcceptedSocket(const int fd, IpPtr ip);

            int fd() noexcept { return base_socket->fd(); }
            const std::string& toString() const { return base_socket->toString(); }

        private:
            BaseSocketPtr base_socket;
        };

        using AcceptedSocketPtr = std::shared_ptr<AcceptedSocket>;
    }
}
