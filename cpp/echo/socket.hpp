#pragma once

#include <memory>
#include <string>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

#include "logger.hpp"

namespace Network {
    enum class SocketType { Stream, Datagram };

    static const int buildSocketFromType(SocketType type) {
        int flags = 0;
        if (type == SocketType::Stream) {
            flags |= SOCK_STREAM;
        } else {
            flags |= SOCK_DGRAM;
        }

        int fd = socket(AF_INET, flags, 0);
        fcntl(fd, F_SETFL, O_NONBLOCK); // macos does not have SOCK_NONBLOCK
        return fd;
    }

    static const int buildListerSocket() {
        int fd = buildSocketFromType(SocketType::Stream);

        int on = 1;
        int rc = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (rc) {
            logger->error("setsockopt returns", rc);
            return -1;
        }

        return fd;
    }

    class Socket {
    public:
        Socket(SocketType t);
        Socket();
        int fd() const { return fd_; }
        void close();
        // change new name of socket? to identify binded socket and connected socket
        const int bind(const std::string host, const uint port);
        const int connect(const std::string host, const uint port);
        const int sockaddrIn(const std::string host, const uint port);

    private:
        sockaddr_in address_;
        int fd_;
    };

    using SocketPtr = std::unique_ptr<Socket>;
}
