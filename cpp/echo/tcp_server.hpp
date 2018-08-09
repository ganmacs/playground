#pragma once

#include <string>

#include "event2/listener.h"

#include "logger.hpp"
#include "socket.hpp"

namespace Tcp {
    class AcceptHandler {
    public:
        virtual void onAccept(int fd) = 0;
    };

    class Server {
    public:
        Server(const std::string host, const uint port);
        ~Server();

        int listen(event_base* base, AcceptHandler&& handler);

    private:
        const std::string host_;
        const uint port_;
        Network::SocketPtr socket_;
        evconnlistener* listener_;
    };

}
