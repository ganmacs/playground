#include "ev_loop.hpp"

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
