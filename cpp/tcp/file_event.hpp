#pragma once

#include <iostream>

#include "event2/event_struct.h"

#include "file_event_type.hpp"
#include "reactor.hpp"

namespace Event {
    class FileEventImpl: public FileEvent {
    public:
        FileEventImpl(Reactor& reactor, int fd, FileReadyCb cb, FileTriggerType type, uint32_t events);
        void assignEvent(uint32_t events);
        virtual void activate(uint32_t events) override;

    private:
        static void onEventCallback(evutil_socket_t, short what, void* arg);

        Libevent::EventBase* base_;
        FileReadyCb callback_;
        int fd_;
        FileTriggerType trigger_;

        event raw_event_;
   };
}
