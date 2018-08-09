#include "tcp_client.hpp"

namespace Tcp {
    Client::Client(const std::string host, const uint port):
        host_{host}, port_{port}, socket_{std::make_unique<Network::Socket>()} {};
}
