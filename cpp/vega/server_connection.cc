#include "server_connection.hpp"

ServerConnection::ServerConnection(vega::network::AcceptedSocketPtr socket)
    :socket_(std::move(socket)) {}
