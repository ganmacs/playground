#include "tcp_server.hpp"

namespace Tcp {
    Server::Server(const std::string host, const uint port):
        host_{host}, port_{port}, socket_{std::make_unique<Network::Socket>()} {};

    Server::~Server() {
        // evconnlistener_free
    }

    void Server::listen(event_base* base) {
        socket_.get()->bind(host_, port_); // XXX

        logger->info("Listen {}:{}", host_, port_);
        // evconnlistener* listener = evconnlistener_new(base, accept_conn_cb, &cm, LEV_OPT_CLOSE_ON_FREE, -1, socket_.get()->fd());
    }
}
