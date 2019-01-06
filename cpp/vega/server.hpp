#pragma once

#include <vector>

#include <ev++.h>

#include "network/socket.hpp"
#include "session/server.hpp"
#include "logger.hpp"
#include "ev_loop.hpp"
#include "server_connection.hpp"

class Server: public EvWatcher {
public:
    Server(const std::string host, const uint32_t port);
     ~Server();
    // ~EvWatcher() {};

    void attach(EvLoop& loop) noexcept;

    /* This method is for ev::io */
    void callback(ev::io& w, int event);

    /* This method is for EvWatch */
    int start() override;
private:
    vega::network::TcpListenSocketPtr socket_;
    ev::io *ev_io_;
    std::vector<vega::network::AcceptedSocketPtr> accepted_sockets_;
};
