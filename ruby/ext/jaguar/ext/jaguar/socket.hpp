#pragma once

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

    const int connect();
    const int request(std::string msg);

private:
    sockaddr_in address_;
    int fd_;
};
