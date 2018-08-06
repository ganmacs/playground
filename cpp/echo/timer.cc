#include <event2/event-config.h>
#include <event2/util.h>

#include "timer.hpp"

namespace Event {
    Timer::Timer(event_base* base, TimerCb cb): cb_{std::move(cb)} {
        evtimer_assign(&raw_event_, base, [](evutil_socket_t, short, void* arg) -> void { static_cast<Timer*>(arg)->cb_(); }, this);
    }

    void Timer::disable() {
        event_del(&raw_event_);
    }

    void Timer::enable(const std::chrono::milliseconds& d) {
        if (d.count() == 0) {
            event_active(&raw_event_, EV_TIMEOUT, 0);
        } else {
            std::chrono::microseconds us = std::chrono::duration_cast<std::chrono::microseconds>(d);
            timeval tv;
            tv.tv_sec = us.count() / 1000000;
            tv.tv_usec = us.count() % 1000000;
            event_add(&raw_event_, &tv);
        }
    }
}
