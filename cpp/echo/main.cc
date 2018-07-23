#include "main.hpp"

static void readCallback() {
    std::cout << "[readCallback] \n";
}

static void writeCallback() {
    std::cout << "[writeCallback] \n";
}

static void eventCallback() {
    std::cout << "[eventCallback] \n";
}

static void cb_func(evutil_socket_t fd, short what, void *arg) {
    std::cout << "[cb_func] \n";
}


static void accept_conn_cb(evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx) {
    event_base *base = evconnlistener_get_base(listener);
    std::cout << "[accept_conn_cb] \n";
    SocketEvent *sev = new SocketEvent { base, fd, SocketEventType::Read|SocketEventType::Write };

    // bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    // bufferevent_setcb(bev, readCallback, NULL, eventCallback, NULL);
    // bufferevent_enable(bev, EV_READ | EV_WRITE);
}

static void accept_error_cb(struct evconnlistener *listener, void *ctx) {
    struct event_base *base = evconnlistener_get_base(listener);
    int err = EVUTIL_SOCKET_ERROR();
    fprintf(stderr, "Got an error %d (%s) on the listener. "
            "Shutting down.\n", err, evutil_socket_error_to_string(err));

    event_base_loopexit(base, NULL);
}

SocketEvent::SocketEvent(event_base* base, int fd, uint32_t events): base_{ base }, fd_{ fd } {
    assignEvents(events);
    event_add(&raw_event_, nullptr);
}

void SocketEvent::assignEvents(uint32_t events) {
    uint32_t what =
        EV_PERSIST |
        (events & SocketEventType::Read ? EV_READ : 0) |
        (events & SocketEventType::Write ? EV_WRITE : 0) |
        (events & SocketEventType::Closed ? EV_CLOSED : 0);
    raw_event_ = *event_new(base_, fd_, what,
                 [](evutil_socket_t, short what, void* arg) -> void {
                     uint32_t events = 0;
                     if (what & EV_READ) {
                         ::readCallback();
                         events |= SocketEventType::Read;
                     }

                     if (what & EV_WRITE) {
                         events |= SocketEventType::Write;
                         ::writeCallback();

                     }

                     if (what & EV_CLOSED) {
                         events |= SocketEventType::Closed;
                         ::eventCallback();
                     }
                 },
                 this);
}

int main(int argc, char **argv) {
    event_base* base { event_base_new() };

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(0); // 0.0.0.0
    sin.sin_port = htons(3000);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(fd, F_SETFL, O_NONBLOCK); // macos does not have SOCK_NONBLOCK
    ::bind(fd, reinterpret_cast<const sockaddr*>(&sin), sizeof(sin));

    int on = 1;
    evconnlistener* listener;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))<0) {
        goto err;
    }

    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof(on))<0) {
        goto err;
    }

    listener = evconnlistener_new(base, accept_conn_cb, NULL, LEV_OPT_CLOSE_ON_FREE, -1, fd);

    if (!listener) {
        perror("Couldn't create listener");
        return 1;
    }
    evconnlistener_set_error_cb(listener, accept_error_cb);

    event_base_loop(base, 0);
    return 0;

 err:
    std::cout << "error\n";
    evutil_closesocket(fd);
    return 1;

}
