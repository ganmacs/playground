#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include "ip.hpp"
#include "../logger.hpp"

namespace vega {
    namespace network {
        enum class SocketType { Stream, Datagram };

        class Socket {
        public:
            Socket(Ip ip);
            ~Socket();

            const int fd() noexcept { return fd_; }

            const int connect() noexcept;
            const int request(std::string msg) noexcept;

            const int openSocket(SocketType type) noexcept;
            const int openListenerSocket() noexcept;

        private:
            Ip ip_;
            int fd_{-1};
        };
    }
}
