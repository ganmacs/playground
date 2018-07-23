#pragma once

#include <iostream>

namespace Event {
    struct FileEventType {
        static const uint32_t Read = 0x1;
        static const uint32_t Write = 0x2;
        static const uint32_t Closed = 0x4;
    };

    // For epoll?
    enum class FileTriggerType {
        Level,
        Edge
    };

    typedef std::function<void(uint32_t events)> FileReadyCb;

    class FileEvent {
    public:
        virtual void activate(uint32_t what) = 0;
    };

    // only use for setting unique_ptr
    typedef std::unique_ptr<FileEvent> FileEventPtr;
}
