#include "socket_event.hpp"

namespace Event {
    SocketEvent::SocketEvent(event_base* base, int fd , SocketEventCb cb, uint32_t events): base_{base}, cb_{cb}, fd_{fd} {
        assignEvents(events);
        event_add(&raw_event_, nullptr);
    }

    void SocketEvent::assignEvents(uint32_t events) {
        uint32_t what =
            EV_PERSIST |
            (events & SocketEventType::Read ? EV_READ : 0) |
            (events & SocketEventType::Write ? EV_WRITE : 0) |
            (events & SocketEventType::Closed ? EV_CLOSED : 0);
        // use event_assign instread of event_new?
        raw_event_ = *event_new(base_, fd_, what,
            [](evutil_socket_t fd, short what, void* arg) -> void {
                SocketEvent* e = static_cast<SocketEvent *>(arg);
                uint32_t events = 0;
                if (what & EV_READ) {
                    events |= SocketEventType::Read;
                }

                if (what & EV_WRITE) {
                    events |= SocketEventType::Write;
                }

                if (what & EV_CLOSED) {
                    events |= SocketEventType::Closed;
                }

                e->cb_(events);
            },
            this);
    }
}
