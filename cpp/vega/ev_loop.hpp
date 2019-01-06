#pragma once

#include <memory>
#include <vector>

#include <ev++.h>

#include "logger.hpp"

class EvWatcher {
public:
    virtual int start() = 0;
    virtual ~EvWatcher() {};
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
