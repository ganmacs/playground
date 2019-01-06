#pragma once

#include <memory>

#include "network/socket.hpp"

class ServerConnection {
public:
    ServerConnection(vega::network::AcceptedSocketPtr socket);

private:
    vega::network::AcceptedSocketPtr socket_;
};
