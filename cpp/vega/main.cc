// #include "unistd.h"
#include "main.hpp"

// Socket::Socket(const std::string host, const uint port) {
//     printf("socket open\n");
//     memset(&address_, 0, sizeof(address_));

//     address_.sin_family = AF_INET;
//     address_.sin_port = htons(port);
//     int rc = ::inet_pton(AF_INET, host.data(), &address_.sin_addr);

//     if (1 != rc) {
//         throw "errro\n";
//     }

//     fd_ = socket(AF_INET, SOCK_STREAM, 0);
//     fcntl(fd_, F_SETFL, O_NONBLOCK); // macos does not have SOCK_NONBLOCK
// }

// Socket::~Socket() {
//     ::close(fd_);
//     printf("socket closed\n");
// }

// void Socket::callback(ev::io& w, int event) {
//     if (event & ev::READ) {
//         read_callback(w);
//     }

//     if (event & ev::WRITE) {
//         write_callback(w);
//     }
// }

// void Socket::read_callback(ev::io& w) {
//     printf("read_callback\n");
// }

// void Socket::write_callback(ev::io& w) {
//     printf("write_callback\n");
// }

// const int Socket::connect() {
//     return ::connect(fd_, reinterpret_cast<const sockaddr*>(&address_), sizeof(struct sockaddr));
// }

// const int Socket::request(std::string msg) {
//     return ::write(fd_, (void *)msg.data(), msg.length());
// }

// class Hello {
// public:
//     Hello() {}

//     void awake(ev::timer& timer, int v) noexcept {
//         printf("hello %d\n", v);
//     }
// };

// void setTimer(ev::default_loop &loop, double sec) {
//     ev::timer *timer1 = new ev::timer(loop);
//     Hello h {};

//     timer1->set<Hello, &Hello::awake>(&h);
//     timer1->set(sec);
//     timer1->start();
// }

// int createListenSocket(std::string addr, uint32_t port, ev::default_loop& loop) {
//     // vega::network::Ip ip {addr, port};
//     auto socket = new vega::network::TcpListenSocket(std::make_unique<vega::network::Ip>(addr, port));

//     io->set<Socket, &Socket::callback>(sock);
//     io->set(sock->fd(), ev::READ);
// }

int main() {
    logger->set_level(spdlog::level::trace);
    // ev::default_loop loop;

    logger->info("start vega");
    EvLoop loop {};
    auto server = new Server("127.0.0.1", 3000);
    server->attach(loop);

    loop.start();
}
