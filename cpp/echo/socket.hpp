#pragma once

#include <memory>
// #include <sys/socket.h>
// #include <sys/types.h>
#include <fcntl.h>

#include "event2/event.h"

#include "logger.hpp"

namespace Socket {
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
}

enum class SocketState {
    Open,
    Closing,
    Closed,
};

#include "event2/listener.h"

class Listener {
public:
    Listener(event_base *baes, int fd): fd_{fd} {
        listener_ = evconnlistener_new(base, accept_conn_cb, &cm, LEV_OPT_CLOSE_ON_FREE, -1, fd_);
    };

private:
    int fd_;
    evconnlistener* listner_;
};

// class ConnectionSocket {
// public:
//     ConnectionSocket();

// private:
//     int fd_;
// };

// using ConnectionSocketPtr = std::unique_ptr<ConnectionSocket>;
