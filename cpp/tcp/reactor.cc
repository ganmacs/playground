#include "reactor.hpp"
#include "file_event.hpp"

namespace Event {
    void Reactor::start() { event_base_loop(base_, 0); }

    FileEventPtr Reactor::registerFileEvent(int fd, FileReadyCb cb, FileTriggerType type, uint32_t event) {
        std::cout << "[registerFileEvent]\n";
        return FileEventPtr { new FileEventImpl(*this, fd, cb, type, event) };
    }
}
