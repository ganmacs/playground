#include "main.hpp"

ServerConnection::ServerConnection(event_base* ebase, evutil_socket_t fd, markClosedConnection cb):
    mark_closed_{cb},
    socket_{std::make_unique<Network::BufferedSocket>(fd)},
    session_{http2::Session::buildServerSession(base())}
{
    auto fn = [this](uint32_t events) -> void { onSocketEvent(events); };
    socket_event_ = std::make_unique<Event::SocketEvent>(ebase, fd, fn,  Event::SocketEventType::Read|Event::SocketEventType::Write);
}

void ServerConnection::onSocketEvent(uint32_t events) {
    if (fd() < 0) {
        logger->warn("invalid fd {}", fd());
        return;
    }

    if (events & Event::SocketEventType::Closed) {
        logger->info("closed fd={}", fd());
        return;
    }

    if ((state_ == network::SocketState::Open) && (events & Event::SocketEventType::Write)) {
        onSocketWrite();
    }

    if ((state_ == network::SocketState::Open) && (events & Event::SocketEventType::Read)) {
        onSocketRead();
    }
}

void ServerConnection::onSocketRead() {
    auto result = socket_.get()->onRead([this](const uint8_t *data, size_t len) -> int {
            auto rv = session_.processData(data, len);
            if (rv == -1) {
                logger->error("processData failed {},", fd());
                return -1;
            }
            return 0;
        });

    session_.sendData();

    if (result.need_close_ || result.end_stream_read_) {
        closeSocket();
    }
}

void ServerConnection::closeSocket() {
    auto sock = socket_.get();

    SPDLOG_TRACE(logger, "closing connection fd={}", sock->fd());
    sock->close();
    state_ = network::SocketState::Closed;
    socket_event_.reset();

    mark_closed_(sock->fd());
}

int ServerConnection::onBeginHeaderCallback(nghttp2_session *session, const nghttp2_frame *frame) {
    SPDLOG_TRACE(logger, "start header process... fd={}, stream_id={}", fd(), frame->hd.stream_id);

    // Skip push promise frame
    if (frame->hd.type != NGHTTP2_HEADERS) {
        std::cout << "[type is NGHTTP2_HEADERS]\n";
        abort();
    }

    //  HEADERS frame is opening?
    if (frame->headers.cat != NGHTTP2_HCAT_REQUEST) {
        // get existing stream
        return 0;
    }

    http2::StreamPtr stream { new http2::Stream(frame->hd.stream_id) };
    streams_.emplace_front(std::move(stream));
    session_.registerStream(frame->hd.stream_id, streams_.front().get());
    return 0;
}

void ServerConnection::onSocketWrite(){
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
    }
}

ssize_t ServerConnection::onSendCallback(const uint8_t* data, const size_t length) {
    SPDLOG_TRACE(logger, "Queueing data {} bytes fd={}", length, fd());
    socket_.get()->write(data, length);
    return length;
};

int ServerConnection::onHeaderCallback(const nghttp2_frame *frame, std::string name, std::string value) {
    SPDLOG_TRACE(logger, "{} => {}", name, value);

    http2::Stream* s = session_.getStream(frame->hd.stream_id);
    if (frame->hd.type == NGHTTP2_HEADERS) {
        // if (frame->headers.cat == NGHTTP2_HCAT_RESPONSE || frame->headers.cat == NGHTTP2_HCAT_HEADERS) {
        s->headers_state_.processHeaderField(std::move(name), std::move(value));
        return 0;
    }

    return 0;
};

static int handleRouteGuideRecordGuide(std::string& buf) {
    routeguide::Point point {};
    if (!point.ParseFromString(buf)) {
        logger->error("parsing request protobuf failed");
        return 1;
    }

    SPDLOG_TRACE(logger, "Point latitude={}, longitude={}", point.latitude(), point.longitude());
    return 0;
}

static int sendFeature(http2::Session &session, http2::Stream *stream, std::string name,  bool end, http2::Headers header) {
    std::string tmp2 {};
    {
        routeguide::Feature feature {};
        routeguide::Point *point = new routeguide::Point();
        point->set_latitude(1);
        point->set_longitude(2);
        feature.set_name(name);
        feature.set_allocated_location(point);
        feature.SerializeToString(&tmp2);
    }

    auto bufw2 = new buffer::BufferWriter();
    bufw2->putUINT8(0);             // non encoding
    bufw2->putUINT32(tmp2.length()); // pre length
    bufw2->append(std::move(tmp2));

    http2::DataFramePtr d2 { new http2::DataFrame(stream->stream_id_, end, header) };
    d2->data_ = bufw2;

    if (stream->sendRespMsg(std::move(d2), session) != 0) {
        logger->error("submitResponse2 is error");
        return 1;
    }

    return 0;
}

static int handleRouteGuideListFeatures(std::string& buf, http2::Session &session, http2::Stream *stream, bool end) {
    routeguide::Rectangle rect {};
    if (!rect.ParseFromString(buf)) {
        logger->error("parsing request protobuf failed");
        return 1;
    }

    SPDLOG_TRACE(logger, "rectangle lo latitude={}, longitude={}", rect.lo().latitude(), rect.lo().longitude());
    SPDLOG_TRACE(logger, "rectangle hi latitude={}, longitude={}", rect.hi().latitude(), rect.hi().longitude());
    std::string tmp {};
    http2::Headers v = {
        {http2::headers::HTTP_STATUS, "200"},
        {http2::headers::CONTENT_TYPE, http2::headers::CONTENT_TYPE_VALUE},
    };

    sendFeature(session, stream, "hoge", false, std::move(v));
    sendFeature(session, stream, "fuga", true, {});
    return 0;
}

void sendReply(http2::Session &session, http2::Stream *stream) {
    helloworld::HelloReply reply {};
    reply.set_message("heyheyhey!!!");

    std::string tmp {};
    reply.SerializeToString(&tmp);

    // XXX
    auto bufw = new buffer::BufferWriter();
    bufw->putUINT8(0);             // non encoding
    bufw->putUINT32(tmp.length()); // pre length
    bufw->append(std::move(tmp));

    http2::Headers v = {
        {http2::headers::HTTP_STATUS, "200"},
        {http2::headers::CONTENT_TYPE, http2::headers::CONTENT_TYPE_VALUE},
    };

    http2::DataFramePtr d { new http2::DataFrame(stream->stream_id_, true, std::move(v)) };
    d->data_ = bufw;

    // XXX: true
    // copy...
    if (stream->sendRespMsg(std::move(d), session) != 0) {
        exit(1);
    }
}

int ServerConnection::onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len) {
    SPDLOG_TRACE(logger, "Receives data {} bytes fd={},  stream_id={}", len, fd(), stream_id);

    http2::Stream *stream = session_.getStream(stream_id);

    buffer::BufferReader buf {(const char *)data, len};
    auto encode_flag =  buf.readUINT8();
    auto plength =  buf.readUINT32();
    std::string s { buf.buffer(), plength };
    sendReply(session_, stream);

    // handleRouteGuideListFeatures(s, session_, stream, false);
    // handleRouteGuideRecordGuide(s);

    return 0;
}

int ServerConnection::onStreamCloseCallback(int32_t stream_id, uint32_t error_code) {
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

/*
  NGHTTP2_DATA
  NGHTTP2_HEADERS
  NGHTTP2_PRIORITY
  NGHTTP2_RST_STREAM
  NGHTTP2_SETTINGS
  NGHTTP2_PUSH_PROMISE
  NGHTTP2_PING
  NGHTTP2_GOAWAY
  NGHTTP2_WINDOW_UPDATE
  NGHTTP2_CONTINUATION
  NGHTTP2_ALTSVC
  NGHTTP2_ORIGIN
*/
int ServerConnection::onFrameRecvCallback(const nghttp2_frame* frame) {
    http2::Stream* stream = session_.getStream(frame->hd.stream_id);

    switch(frame->hd.type) {
    case NGHTTP2_GOAWAY: {
        SPDLOG_TRACE(logger, "[TODO]Recieved GOAWAY frame fd={}, stream_id={}", fd(), frame->hd.stream_id);
        // handleGoawayFrame()
        break;
    }
    case NGHTTP2_DATA: {
        stream->remote_end_stream_ = frame->hd.flags & NGHTTP2_FLAG_END_STREAM;

        SPDLOG_TRACE(logger, "Recieved DATA frame fd={}, stream_id={}, end_stream={}", fd(), frame->hd.stream_id, stream->remote_end_stream_);
        break;
    }
    case NGHTTP2_HEADERS: {
        stream->remote_end_stream_ = frame->hd.flags & NGHTTP2_FLAG_END_STREAM;

        SPDLOG_TRACE(logger, "Recieved HEADERS frame fd={}, stream_id={}, end_stream={}", fd(), frame->hd.stream_id, stream->remote_end_stream_);

        // sendReply(session_, stream);
        // std::string s {};
        // handleRouteGuideListFeatures(s, session_, stream, false);

        switch (frame->headers.cat) {
        case NGHTTP2_HCAT_RESPONSE: {
            std::cout << "[Frame Recv] HEADERS NGHTTP2_HCAT_RESPONSE \n";
            break;
        }
        case NGHTTP2_HCAT_REQUEST: {
            std::cout << "[Frame Recv] HEADERS NGHTTP2_HCAT_REQUEST \n";
            break;
        }
        case NGHTTP2_HCAT_HEADERS: {
            SPDLOG_TRACE(logger, "This headers is END_HEADER");
            break;
        }
        default: {
            return 1;
        };
        }
    }
    case NGHTTP2_RST_STREAM: {
        SPDLOG_TRACE(logger, "Recieved RST_STREAM (remote closed) frame fd={}, stream_id={}, error_code={}", fd(), frame->hd.stream_id, frame->rst_stream.error_code);
        // stream.closed() ?
        break;
    }
    }

    return 0;
}

int ServerConnection::onFrameSendCallback(const nghttp2_frame* frame) {
    SPDLOG_TRACE(logger, "sent frame type={}", static_cast<uint64_t>(frame->hd.type));

    switch(frame->hd.type) {
    case NGHTTP2_GOAWAY: {
        SPDLOG_TRACE(logger, "GOAWAY");
        break;
    }
    case NGHTTP2_RST_STREAM: {
        SPDLOG_TRACE(logger, "RST_STREAM");
        break;
    }
    case NGHTTP2_HEADERS: {
        http2::Stream* stream = session_.getStream(frame->hd.stream_id);
        stream->local_end_stream_ = frame->hd.flags & NGHTTP2_FLAG_END_STREAM;
        SPDLOG_TRACE(logger, "sent end stream={}", stream->local_end_stream_);

        break;
    }
    case NGHTTP2_DATA: {
        http2::Stream* stream = session_.getStream(frame->hd.stream_id);
        // std::string s {};
        // if (stream->sending_) {
        //     handleRouteGuideListFeatures(s, session_, stream, true);
        // }

        stream->local_end_stream_ = frame->hd.flags & NGHTTP2_FLAG_END_STREAM;
        SPDLOG_TRACE(logger, "sent end stream={}", stream->local_end_stream_);
        break;
    }
    }
    return 0;
}

ConnectionManager::ConnectionManager(event_base *base):
    base_{base},
    connection_cleaner_{ Event::TimerPtr { new Event::Timer(base, [this]() -> void { clearUnavailableConnection(); }) }} {}


void ConnectionManager::clearUnavailableConnection() {
    for (auto c : unavailable_connections_) {
        SPDLOG_TRACE(logger, "erase fd={} from active connections", c);
        if (active_connections_.erase(c) == 0) {
            logger->warn("fd={} does not exist in active_connections", c);
        }
    }
    unavailable_connections_.clear();
}

void ConnectionManager::deleteConnection(int fd) {
    SPDLOG_TRACE(logger, "enqueue fd={} into unavailable_connections", fd);
    unavailable_connections_.emplace_back(fd);
    connection_cleaner_.get()->enable(std::chrono::milliseconds(0));
}

void ConnectionManager::registerConnection(const int fd, ServerConnectionPtr&& conn) {
    active_connections_.emplace(fd, std::move(conn));
}

void ConnectionManager::onAccept(int fd) {
    // Pass unavailable_connections_ ?
    ServerConnectionPtr conn = std::make_unique<ServerConnection>(base_, fd, [this](int fd) -> void { deleteConnection(fd); });

    if (conn.get()->state_ != network::SocketState::Closed) {
        registerConnection((int)fd, std::move(conn));
    }
}

int main(int argc, char **argv) {
    logger->set_level(spdlog::level::trace);

    auto v = std::getenv("CLIENT");
    event_base* base { event_base_new() };

    // XXX
    if (v == nullptr) {
        logger->info("starting server...");
        Tcp::Server server { "0.0.0.0", 3000 };
        auto cm = new ConnectionManager(base);
        server.listen(base, std::move(*cm));
        event_base_loop(base, 0);

        delete cm;
    } else {
        logger->info("starting request...");

        auto c = ClientConnection::connect(base, "127.0.0.1", 3000);
        std::thread t([&]{ event_base_loop(base, 0); });

        c.request();

        int second = 2;
        sleep(second);

        logger->info("request2===");
        c.request2();

        second = 10;
        sleep(second);
    }

    return 0;
}
