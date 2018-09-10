#pragma once

#include <ev++.h>

#include <string>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

class Socket {
public:
    Socket(const std::string host, const uint port);
    ~Socket();

    const int fd() { return fd_; }

    const int connect();
    const int request(std::string msg);

    void callback(ev::io& w, int event);
private:

    void read_callback(ev::io& w);
    void write_callback(ev::io& w);
    sockaddr_in address_;
    int fd_;
};
