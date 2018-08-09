#pragma once

#include <functional>

#include "event2/event.h"
#include "event2/event_struct.h"

namespace Event {
    using SocketEventCb = std::function<void(uint32_t events)>;

    struct SocketEventType {
        static const uint32_t Read = 0x1;
        static const uint32_t Write = 0x2;
        static const uint32_t Closed = 0x4;
    };

    class SocketEvent {
    public:
        SocketEvent(event_base* base, int fd, SocketEventCb cb, uint32_t events);
        ~SocketEvent() { event_del(&raw_event_); };
        void assignEvents(uint32_t events);

    private:
        static void onEventCallback(evutil_socket_t, short what, void* arg);

        event_base* base_;
        SocketEventCb cb_;
        int fd_;
        event raw_event_;
    };

    using SocketEventPtr = std::unique_ptr<SocketEvent>;
}
