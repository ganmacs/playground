#include "server.hpp"

Server::Server(const std::string host, const uint32_t port):
    socket_(std::make_unique<vega::network::TcpListenSocket>(host, port)),
    ev_io_(nullptr) {};

Server::~Server() {
    delete ev_io_;
}

void Server::attach(EvLoop& loop) noexcept {
    // TODO: check attached
    ev_io_ = new ev::io(*loop.base());
    const auto sock = socket_.get();
    ev_io_->set<Server, &Server::callback>(this);
    ev_io_->set(sock->fd(), ev::READ);

    loop.attach(this);
}

int Server::start() {
    if (ev_io_ == nullptr) {
        logger->error("Does not start due to Server does not attach to loop");
        return -1;
    }

    logger->info("Start server, listening {}", socket_->toString());

    if (socket_->doBind() == -1) {
        logger->error("bind failed {}",  socket_->toString());
        return -1;
    }

    // TODO: 10?
    if (socket_->doListen(10) == -1) {
        logger->error("listen failed {}",  socket_->toString());
        return -1;
    }

    if (ev_io_ == nullptr) {
        logger->error("ev_io_ is not initialized yet");
        return -1;
    }

    ev_io_->start();
    return 0;
}

#include <nghttp2/nghttp2.h>

constexpr std::size_t BUFFER_SIZE = 4096;
using BufferPtr = std::unique_ptr<std::array<char, BUFFER_SIZE>>;

class Connection {
public:
    Connection(vega::network::AcceptedSocketPtr socket):
        socket_(socket),
        read_buffer_(std::make_unique<std::array<char, BUFFER_SIZE>>()),
        write_buffer_(std::make_unique<std::array<char, BUFFER_SIZE>>()),
        session_(std::make_unique<vega::session::Server>(socket))
    {
        watcher_.set<Connection, &Connection::callback>(this);
        watcher_.set(socket->fd(), ev::READ | ev::WRITE);
        // session_ = std::make_unique<Server>(this);
    }

    void start() noexcept {
        watcher_.start();
    }

    void close() noexcept {
        // ::close(socket_->close());
    }

    void callback(ev::io& w, int event) {
        if (event & ev::WRITE) {
            onWrite(w);
        }

        if (event & ev::READ) {
            onRead(w);
        }
    }

private:
    static constexpr int WOULDBLOCK = EAGAIN;
    std::shared_ptr<vega::network::AcceptedSocket> socket_;
    ev::io watcher_;            // TODO: specify loop?
    BufferPtr read_buffer_;
    BufferPtr write_buffer_;
    vega::session::ServerPtr session_;

    void onRead(ev::io& w);
    void onWrite(ev::io&);

    // {
    // SPDLOG_TRACE(logger, "write fd={}", w.fd);

    // std::cout
    //     << "write()"
    //     << std::endl;

    // ssize_t sent_bytes = 0;
    // while (sent_bytes < received_bytes) {
    //     ssize_t result = send(
    //             w.fd,
    //             &buffer[sent_bytes],
    //             received_bytes - sent_bytes,
    //             0);

    //     std::cout
    //         << std::setw(4) << " " << result << " bytes sent"
    //         << std::endl;

    //     if (result == -1) {
    //         if (errno == EAGAIN) {
    //             return;
    //         }
    //         throw std::runtime_error(strerror(errno));
    //     }

    //     sent_bytes += result;
    // }

    // received_bytes = 0;
    // w.stop();

    //this->close();
    // }

};

void Connection::onWrite(ev::io&) {};

void Connection::onRead(ev::io &w) {
    auto buffer = read_buffer_.get();
    auto size = recv(w.fd, buffer->data(), buffer->size(), 0);

    if (size == 0) {
        SPDLOG_TRACE(logger, "zero? {} bytes received. fd={}", size, w.fd);
        // w.stop();
        // this->close();
        // close?
        return;
    } else if (size < 0) {
        if (errno == WOULDBLOCK) {
            return;
        } else {
            logger->error("fd={} is error {}, {}", w.fd, strerror(errno), errno);
            abort();
        }
    } else {
        SPDLOG_TRACE(logger, "{} bytes received. fd={}", size, w.fd);
        auto r = session_.get()->onRead(reinterpret_cast<uint8_t *>(buffer->data()), size); // XXX
        if (r < 0) {
            logger->error("session read is error fd={} {}, {}", w.fd, strerror(errno), errno);
            abort();
        }
    }
}

void Server::callback(ev::io& w, int event) {
    SPDLOG_TRACE(logger, "Server Ready to read: fd={}, {}", w.fd, event);

    sockaddr_in remote_sockaddr_in;
    socklen_t rsi_length = sizeof(remote_sockaddr_in);
    const auto fd = ::accept(w.fd, reinterpret_cast<sockaddr*>(&remote_sockaddr_in), &rsi_length);
    if (fd == -1) {
        logger->error("Server `accept` faled: {}", strerror(errno));
        return;
    }
    auto socket = std::make_shared<vega::network::AcceptedSocket>(fd, std::make_unique<vega::network::Ip>(&remote_sockaddr_in));
    SPDLOG_TRACE(logger, "remote host is {}, fd={}", socket->toString(), fd);

    accepted_sockets_.emplace_back(socket);
    auto conn = new Connection(socket);
    conn->start();

    // auto connection = new ServerConnection(std::move(socket));
}
