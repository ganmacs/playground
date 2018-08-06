#pragma once

#include <functional>
#include <chrono>

#include "event2/event.h"
#include "event2/event_struct.h"

namespace Event {
    using TimerCb = std::function<void()>;

    class Timer {
    public:
        Timer(event_base* base, TimerCb cb);
        void disable();
        void enable(const std::chrono::milliseconds& d);

        TimerCb cb_;
    private:
        event raw_event_;
    };

    using TimerPtr = std::unique_ptr<Timer>;
}
