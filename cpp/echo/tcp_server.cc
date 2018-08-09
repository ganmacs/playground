#include "tcp_server.hpp"

#include "event2/listener.h"

namespace Tcp {
    Server::Server(const std::string host, const uint port):
        host_{host}, port_{port}, socket_{std::make_unique<Network::Socket>()} {};

    Server::~Server() {
        // evconnlistener_free
    }

    static void acceptCallback(evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *arg) {
        SPDLOG_TRACE(logger, "Accept connection: fd={}", fd);
        auto *handler = static_cast<AcceptHandler*>(arg);
        handler->onAccept(fd);
    }

    static void acceptErrorCallback(struct evconnlistener *listener, void *ctx) {
        struct event_base *base = evconnlistener_get_base(listener);
        int err = EVUTIL_SOCKET_ERROR();
        logger->error("Got an error %d (%s) on the listener. Shutting down.", err, evutil_socket_error_to_string(err));
        event_base_loopexit(base, NULL);
    }

    int Server::listen(event_base* base, AcceptHandler&& handler) {
        if (socket_.get()->bind(host_, port_) < 0) {
            return -1;
        }

        logger->info("Listen {}:{}", host_, port_);
        listener_ = evconnlistener_new(base, acceptCallback, &handler, LEV_OPT_CLOSE_ON_FREE, -1, socket_.get()->fd());
        if (!listener_) {
            logger->error("Couldn't create listener");
            return -1;
        }

        evconnlistener_set_error_cb(listener_, acceptErrorCallback);
        return 0;
    }
}
