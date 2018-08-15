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

void ClientConnection::request() {
    SPDLOG_TRACE(logger, "Sending request");

    helloworld::HelloRequest req {};
    req.set_name("muyclient");

    std::string tmp {};
    req.SerializeToString(&tmp);

    // XXX
    auto bufw = new buffer::BufferWriter();
    bufw->putUINT8(0);             // non encoding
    bufw->putUINT32(tmp.length()); // pre length
    bufw->append(std::move(tmp));

    std::map<std::string, std::string> v = {
        {http2::headers::METHOD, "POST"},
        {http2::headers::SCHEME, "http"},
        {http2::headers::PATH, "/helloworld.Greeter/SayHello"},
        // {http2::headers::GRPC_TIMEOUT, "10"}, // XXX
        {http2::headers::CONTENT_TYPE, http2::headers::CONTENT_TYPE_VALUE},
        // {http2::headers::GRPC_ENCODING, "gzip"},
        {":authority",  "echo.server:3000"}
    };

    http2::DataFrame d { 0, true, std::move(v) };
    d.data_ = bufw;

    auto stream_id = session_.submitRequest(d);
    SPDLOG_TRACE(logger, "Submit request to stream_id={}", stream_id);
    session_.sendData();
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
    // SPDLOG_TRACE(logger, "fd={} is write-ready", fd());
    if (!socket_.get()->needFlush()) {
        return;
    }

    uint64_t bytes_written = 0;

    // TODO: check connection is active
    do {
        if (!socket_.get()->needFlush()) {
            // keep open
            break;
        }

        int rc = socket_.get()->flush();
        if (rc == -1) {
            if (errno == EAGAIN) {
                // keep open
            } else {
                logger->error("flush failed {}", strerror(errno));
                // close
            }

            break;
        } else {
            bytes_written += rc;
        }
    } while(true);


    SPDLOG_TRACE(logger, "Sending data {} bytes fd={}", bytes_written, fd());
    if (bytes_written > 0) {
        // TODO
        session_.sendData();
    }
}

void ClientConnection::onSocketRead(){
    SPDLOG_TRACE(logger, "ready ready");
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
    SPDLOG_TRACE(logger, "Queueing data {} bytes fd={}", length, fd());
    socket_.get()->write(data, length);
    return length;
    return 0;
}

int ClientConnection::onBeginHeaderCallback(nghttp2_session* session, const nghttp2_frame *frame) {
    // skip push prom
    if (frame->hd.type != NGHTTP2_HEADERS)  {
        return 0;
    }

    http2::StreamPtr stream { new http2::Stream(frame->hd.stream_id) };
    // need?
    streams_.emplace_front(std::move(stream));
    session_.registerStream(frame->hd.stream_id, streams_.front().get());

    return 0;
}

void handleHelloWorld(std::string buf) {
    helloworld::HelloReply rep {};
    if (!rep.ParseFromString(buf)) {
        logger->error("parsing request protobuf failed");
        return;
    }

    SPDLOG_TRACE(logger, "handlhelloworld message {}", rep.message());
}

int ClientConnection::onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len) {
    SPDLOG_TRACE(logger, "Receives data {} bytes fd={},  stream_id={}", len, fd(), stream_id);

    http2::Stream *stream = session_.getStream(stream_id);

    buffer::BufferReader buf {(const char *)data, len};
    auto encode_flag =  buf.readUINT8();
    auto plength =  buf.readUINT32();
    std::string s { buf.buffer(), plength };

    handleHelloWorld(std::move(s));

    // handle!
    return 0;
}

int ClientConnection::onFrameRecvCallback(const nghttp2_frame* frame) {
    switch(frame->hd.type) {
    case NGHTTP2_GOAWAY: {
        SPDLOG_TRACE(logger, "[TODO]Recieved GOAWAY frame fd={}, stream_id={}", fd(), frame->hd.stream_id);
        break;
    }
    case NGHTTP2_DATA: {
        SPDLOG_TRACE(logger, "Recieved DATA frame fd={}, stream_id={}", fd(), frame->hd.stream_id);
        break;
    }
    case NGHTTP2_HEADERS: {
        SPDLOG_TRACE(logger, "Recieved HEADERS frame fd={}, stream_id={}", fd(), frame->hd.stream_id);
        break;
    }
    case NGHTTP2_SETTINGS: {
        SPDLOG_TRACE(logger, "Recieved SETTINGS frame fd={}, stream_id={}", fd(), frame->hd.stream_id);
        break;
    }
    case NGHTTP2_RST_STREAM: {
        SPDLOG_TRACE(logger, "Recieved RST_STREAM frame fd={}, stream_id={}, error_code={}({})",
                     fd(),
                     frame->hd.stream_id,
                     frame->rst_stream.error_code, nghttp2_http2_strerror(frame->rst_stream.error_code));
        break;
    }
    }

    return 0;
}

int ClientConnection::onInvalidFrameRecvCallback(const nghttp2_frame *frame, int error_code) {
    SPDLOG_TRACE(logger, "onInvalidFrameRecvCallback error_code={}, {}, stream_id={}", error_code, nghttp2_strerror(error_code), frame->hd.stream_id);
    return 0;
}

int ClientConnection::onHeaderCallback(const nghttp2_frame* frame, std::string name, std::string value) {
    switch (frame->hd.type) {
    case NGHTTP2_HEADERS: {
        SPDLOG_TRACE(logger, "{} => {}", name, value);
        break;
    }
    }

    return 0;
}

int ClientConnection::onStreamCloseCallback(int32_t stream_id, uint32_t error_code) {
    http2::Stream* stream = session_.getStream(stream_id);

    if (stream) {
        if (stream->remote_end_stream_) {
            SPDLOG_TRACE(logger, "stream={} fd={} is closed by peer", stream_id, fd());
        }
    }

    // remove stream from streams
    session_.registerStream(stream_id, nullptr);

    return 0;
}

namespace Tcp {
}
