#pragma once

#include <string>

#include "event2/listener.h"

#include "logger.hpp"
#include "socket.hpp"

namespace Tcp {
    class Server {
    public:
        Server(const std::string host, const uint port);
        ~Server();

        void listen(event_base* base);
    private:

        const std::string host_;
        const uint port_;
        Network::SocketPtr socket_;
    };

}
