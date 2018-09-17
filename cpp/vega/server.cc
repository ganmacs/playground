#include "server.hpp"

EvLoop::EvLoop(): loop_(new ev::default_loop()) {}
EvLoop::~EvLoop() {
    delete loop_;
}

int EvLoop::attach(EvWatcher *watcher) noexcept {
    EvWatcherShdPtr v(watcher);
    watchers_.emplace_back(v);
    return 0;
}

int EvLoop::start() noexcept {
    if (watchers_.size() == 0) {
        logger->error("watcher did not attach to ev::loop");
        return -1;
    }

    for (auto w: watchers_) {
        const auto rv = w->start();
        if (rv == -1) {
            return -1;
        }
    }

    loop_->run(0);
    return 0;
}

Server::Server(const std::string host, const uint32_t port):
    socket_(std::make_unique<vega::network::TcpListenSocket>(host, port)),
    ev_io_(nullptr) {};

Server::~Server() {
    delete ev_io_;
}

void Server::attach(EvLoop& loop) noexcept {
    // TODO:
    ev_io_ = new ev::io(*loop.base());
    const auto sock = socket_.get();
    ev_io_->set<Server, &Server::callback>(this);
    ev_io_->set(sock->fd(), ev::READ);

    loop.attach(this);
}

int Server::start() {
    if (ev_io_ == nullptr) {
        logger->error("ev_io_ is not initialized yet");
        return -1;
    }

    ev_io_->start();
    return 0;
}

void Server::callback(ev::io& w, int event) {
    SPDLOG_TRACE(logger, "Server Ready to read: fd={}, {}", w.fd, event);

    sockaddr_in remote_sockaddr_in;
    socklen_t rsi_length = sizeof(remote_sockaddr_in);
    const auto fd = ::accept(w.fd,reinterpret_cast<sockaddr*>(&remote_sockaddr_in), &rsi_length);
    if (fd == -1) {
        logger->error("Server `accept` faled: {}", strerror(errno));
        return;
    }
}
