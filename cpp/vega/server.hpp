#pragma once

#include <ev++.h>
#include <vector>

#include "logger.hpp"
#include "network/socket.hpp"

class EvWatcher {
public:
    virtual int start() = 0;
    virtual ~EvWatcher() = 0;
};
using EvWatcherShdPtr = std::shared_ptr<EvWatcher>;

class EvLoop {
public:
    EvLoop();
    ~EvLoop();
    // EvLoop(ev::default_loop); // for specify loop

    int attach(EvWatcher* watcher) noexcept;
    int start() noexcept;
    ev::default_loop* base() noexcept { return loop_; }

private:
    ev::default_loop* loop_;
    std::vector<EvWatcherShdPtr> watchers_;
};

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
};
