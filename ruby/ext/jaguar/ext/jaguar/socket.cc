#include <stdio.h>
#include "socket.hpp"

Socket::Socket(const std::string host, const uint port) {
    printf("socket open\n");
    memset(&address_, 0, sizeof(address_));

    address_.sin_family = AF_INET;
    address_.sin_port = htons(port);
    int rc = ::inet_pton(AF_INET, host.data(), &address_.sin_addr);

    if (1 != rc) {
        throw "errro\n";
    }

    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(fd_, F_SETFL, O_NONBLOCK); // macos does not have SOCK_NONBLOCK
}

const int Socket::connect() {
    return ::connect(fd_, reinterpret_cast<const sockaddr*>(&address_), sizeof(struct sockaddr));
}

const int Socket::request(std::string msg) {
    return ::write(fd_, (void *)msg.data(), msg.length());
}

Socket::~Socket() {
    ::close(fd_);
    printf("socket closed\n");
}
