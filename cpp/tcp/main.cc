#include "event2/listener.h"
#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/event.h"

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

struct event_base;
extern "C" {
    void event_base_free(event_base*);
}

namespace Libevent {
    typedef event_base EventBase;
}


// typedef CSmartPtr<event_base, event_base_free> BasePtr;


class Socket {
public:
    Socket(int fd): fd_{fd} {}

    int fd() { return fd_; }
    void close() { ::close(fd_); }

private:
    const int fd_;
};

class Connection {
    Connection(): buffer_(evbuffer_new()) {}
    ~Connection() { evbuffer_free(buffer_); }

private:
    evbuffer* buffer_;
};

class Server {
public:
    static void listenCallback(evconnlistener*, evutil_socket_t fd, sockaddr* remote_addr, int remote_addr_len, void* arg);

    Server(int fd): base_{ event_base_new() }, s_{fd} {
        int on = 1;
        int rc = setsockopt(s_.fd(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (rc) {
            s_.close();
            printf( "rc is -1\n");
        }

    }

    int setup(int port) {
        if (bind(port)< 0) {
            printf("failed binding\n");
            return -1;
        }
        evconnlistener_new(base_, listenCallback, this, 0, -1, s_.fd());
        return 1;
    }

    void start() {
        event_base_loop(base_, 0);
    }
private:
    Libevent::EventBase* base_;
    Socket s_;

    int bind(int port) {
        sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(0);
        addr.sin_port = htons(port);

        return ::bind(s_.fd(), reinterpret_cast<const sockaddr*>(&addr), sizeof(addr));
    }
};


void Server::listenCallback(evconnlistener*, evutil_socket_t fd, sockaddr* remote_addr, int remote_addr_len, void* arg) {
    Server* server = static_cast<Server*>(arg);

    // printf("received %d\n", fd, );
}


int main(int argc, char *argv[])
{
    Server s { socket(AF_INET, SOCK_STREAM, 0) };
    if (s.setup(3000) < 0) {
        printf("failed" );
    }
    s.start();
    return 0;
}
