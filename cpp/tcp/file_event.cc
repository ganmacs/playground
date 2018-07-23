#include "file_event.hpp"

namespace Event {
    FileEventImpl::FileEventImpl(Reactor& reactor, int fd, FileReadyCb cb, FileTriggerType type, uint32_t events):
        base_{ reactor.base() }, callback_{ cb }, fd_{ fd }, trigger_{ type } {
            assignEvent(events);
            event_add(&raw_event_, nullptr);
    }

    void FileEventImpl::assignEvent(uint32_t events) {
        short what =
            (trigger_ == FileTriggerType::Edge ? EV_ET : 0) |
            (events & FileEventType::Read ? EV_READ : 0) |
            (events & FileEventType::Write ? EV_WRITE : 0) |
            (events & FileEventType::Closed ? EV_CLOSED : 0);
        event_assign(&raw_event_, base_, fd_, what, onEventCallback, this);
    }

    void FileEventImpl::onEventCallback(evutil_socket_t, short what, void* arg) {
        FileEventImpl* event = static_cast<FileEventImpl *>(arg);
        uint32_t events = 0;

        if (EV_READ & what) {
            events |= FileEventType::Read;
        }

        if (EV_WRITE & what) {
            events |= FileEventType::Write;
        }

        if (EV_CLOSED & what) {
            events |= FileEventType::Closed;
        }

        event->callback_(events);
    }

    void FileEventImpl::activate(uint32_t what) {
        uint32_t events = 0;

        if (FileEventType::Read & what) {
            events |= EV_READ;
        }

        if (FileEventType::Write & what) {
            events |= EV_WRITE;
        }

        if (FileEventType::Closed & what) {
            events |= EV_CLOSED;
        }

        event_active(&raw_event_, events, 0);
    }
}
