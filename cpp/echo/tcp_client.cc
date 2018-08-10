#include "tcp_client.hpp"

// TODO: check connected socket
ClientConnection::ClientConnection(event_base* base, Network::SocketPtr socket):
    base_{base},
    socket_{std::make_unique<Network::BufferedSocket>(std::move(socket))},
    session_{http2::Session::buildClientSession(this)}
{
    auto fn = [this](uint32_t events) -> void { onSocketEvent(events); };
    socket_event_ = std::make_unique<Event::SocketEvent>(base_, socket_->fd(), fn,  Event::SocketEventType::Read|Event::SocketEventType::Write);
}

ClientConnection ClientConnection::connect(event_base* base, const std::string host, const uint port) {
    Network::Socket sock {Network::buildSocketFromType(Network::SocketType::Stream)};
    // check
    sock.connect(host, port);
    return {base, std::make_unique<Network::Socket>(sock)};
}


void ClientConnection::onSocketEvent(uint32_t events) {
    if (socket_->fd() < 0) {
        logger->warn("invalid fd {}", socket_->fd());
        return;
    }

    if (events & Event::SocketEventType::Closed) {
        logger->info("closed fd={}", socket_->fd());
        return;
    }

    if (events & Event::SocketEventType::Write) {
        onSocketWrite();
    }

    if (events & Event::SocketEventType::Read) {
        onSocketRead();
    }
}


void ClientConnection::onSocketWrite() {
    session_.sendRequest();
}

void ClientConnection::onSocketRead(){
    auto result = socket_.get()->onRead([this](const uint8_t *data, size_t len) -> int {
            auto rv = session_.processData(data, len);
            if (rv == -1) {
                logger->error("processData failed {},", fd());
                return -1;
            }
            return 0;
    });

}

ssize_t ClientConnection::onSendCallback(const uint8_t *data, size_t length) {
}

int ClientConnection::onBeginHeaderCallback(nghttp2_session* session, const nghttp2_frame *frame) {
}

int ClientConnection::onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len) {
}

int ClientConnection::onFrameRecvCallback(const nghttp2_frame* frame) {
}

int ClientConnection::onHeaderCallback(const nghttp2_frame* frame, std::string name, std::string value) {
}

int ClientConnection::onStreamCloseCallback(int32_t stream_id, uint32_t error_code) {
}

namespace Tcp {
}
