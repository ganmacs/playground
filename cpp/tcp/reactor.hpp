#pragma once

#include <iostream>

#include "event2/event.h"
#include "file_event_type.hpp"

namespace Libevent {
    typedef event_base EventBase;
}

namespace Event {
    class Reactor {
    public:
        Reactor(): base_{ event_base_new() } {};

        void start();
        Libevent::EventBase* base() { return base_; };
        FileEventPtr registerFileEvent(int fd, FileReadyCb cb, FileTriggerType type, uint32_t event);
    private:
        Libevent::EventBase* base_;
    };
}
