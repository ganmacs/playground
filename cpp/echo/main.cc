#include <err.h>
#include <cstring>
#include <fstream>

#include "main.hpp"

int Buffer::add(const void* data, uint64_t size) {
    return evbuffer_add(buffer_, data, size);
}

// buffer is not correct position
int Buffer::write(const int fd) {
    const uint64_t MaxSlices = 16; // 16?
    RawSlice slices[MaxSlices];
    const uint64_t num_slices = std::min(getRawSlice(slices, MaxSlices), MaxSlices);
    iovec iov[num_slices];

    uint64_t write_count = 0;
    for (uint64_t i = 0; i < num_slices; i++) {
        if (slices[i].mem_ == nullptr || slices[i].len_ == 0) {
            continue;
        }
        iov[i].iov_base = slices[i].mem_;
        iov[i].iov_len = slices[i].len_;
        write_count++;
    }
    if (write_count == 0) {
        return 0;
    }

    const ssize_t rc = writev(fd, iov, write_count);
    if (rc > 0) {
        drain(static_cast<uint64_t>(rc));
    }

    return rc;
}


void Buffer::takeIn(Buffer& b) {
    int rc = evbuffer_add_buffer(buffer_, b.buffer_);
    if (rc != 0) {
        std::cout << "[takein] miss\n";
    }
}

void Buffer::commit(RawSlice* iovecs, uint64_t const size) {
    int ret = evbuffer_commit_space(buffer_, reinterpret_cast<evbuffer_iovec*>(iovecs), size);
    if (ret != 0) {
        puts("evbuffer_commit_sapce failed");
        exit(1);
    }
}

int Buffer::read(const int fd, const uint64_t max_length) {
    const uint64_t MaxSlices = 2;
    RawSlice slices[MaxSlices];
    const uint64_t num_slices = reserve(max_length, slices, MaxSlices);
    iovec iov[num_slices];
    uint64_t num_bytes_to_read = 0;

    uint64_t i = 0;
    // TODO
    for (; i < num_slices; i++) {
        iov[i].iov_base = slices[i].mem_;
        const size_t len = std::min(slices[i].len_, static_cast<size_t>(max_length - num_bytes_to_read));
        iov[i].iov_len = len;
        num_bytes_to_read += max_length;
    }

    const ssize_t rc = ::readv(fd, iov, static_cast<int>(i));
    if (rc < 0) {
        return rc;
    }

    uint64_t num_to_commit = rc;
    uint64_t j = 0;
    while (num_to_commit > 0) {
        slices[j].len_ = std::min(slices[j].len_, static_cast<size_t>(num_to_commit));
        num_to_commit -= slices[j].len_;
        j++;
    }

    commit(slices, j);
    return rc;
}

void Buffer::drain(const uint64_t len) {
    if (len <= 0) {
        puts("drain must not call with negative value");
        exit(1);
    }

    int rc = evbuffer_drain(buffer_, len);
    if (rc != 0) {
        puts("drain error %s");
        exit(1);
    }
}

uint64_t Buffer::reserve(uint64_t const length, RawSlice* iovecs, uint64_t const iovecs_num) {
    int ret = evbuffer_reserve_space(buffer_, length, reinterpret_cast<evbuffer_iovec*>(iovecs), iovecs_num);
    if (ret < 0) {
        printf("%d\n", ret);
        exit(1);
    }
    return ret;
}

static void accept_conn_cb(evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx) {
    SPDLOG_TRACE(logger, "Accept connection: fd={}", fd);
    ConnectionManager *cm = static_cast<ConnectionManager*>(ctx);

    event_base *base = evconnlistener_get_base(listener);

    ServerConnectionPtr conn = std::make_unique<ServerConnection>(base, fd, [cm](int fd) -> void { cm->deleteConnection(fd); });
    if (conn.get()->state_ != network::SocketState::Closed) {
        cm->registerConnection((int)fd, std::move(conn));
    }
}

static void accept_error_cb(struct evconnlistener *listener, void *ctx) {
    struct event_base *base = evconnlistener_get_base(listener);
    int err = EVUTIL_SOCKET_ERROR();
    fprintf(stderr, "Got an error %d (%s) on the listener. "
            "Shutting down.\n", err, evutil_socket_error_to_string(err));

    event_base_loopexit(base, NULL);
}

SocketEvent::SocketEvent(event_base* base, int fd , SocketEventCb cb, uint32_t events): base_{base}, cb_{cb}, fd_{fd} {
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
                            [](evutil_socket_t fd, short what, void* arg) -> void {
                                SocketEvent* e = static_cast<SocketEvent *>(arg);
                                uint32_t events = 0;
                                if (what & EV_READ) {
                                    events |= SocketEventType::Read;
                                }

                                if (what & EV_WRITE) {
                                    events |= SocketEventType::Write;
                                }

                                if (what & EV_CLOSED) {
                                    events |= SocketEventType::Closed;
                                }

                                e->cb_(events);
                            },
                 this);
}

ServerConnection::ServerConnection(event_base* ebase, evutil_socket_t fd, markClosedConnection cb):
    fd_{fd},
    session_{http2::Session { base() }},
    mark_closed_{cb}
{
    auto fn = [this](uint32_t events) -> void { onSocketEvent(events); };
    socket_event_ = std::make_unique<SocketEvent>(ebase, fd, fn, SocketEventType::Read|SocketEventType::Write|SocketEventType::Closed);
}

void ServerConnection::onSocketEvent(uint32_t events) {
    if (fd_ < 0) {
        logger->warn("invalid fd {}", fd_);
        return;
    }

    if (events & SocketEventType::Closed) {
        logger->info("closed fd={}", fd_);
        return;
    }

    if ((state_ == network::SocketState::Open) && (events & SocketEventType::Write)) {
        onSocketWrite();
    }

    if ((state_ == network::SocketState::Open) && (events & SocketEventType::Read)) {
        onSocketRead();
    }
}

void ServerConnection::onSocketRead(){
    IoResult result = readData();
    SPDLOG_TRACE(logger, "fd={} is read-ready and receives data is {} bytes", fd_, result.bytes_processed_);

    if (result.bytes_processed_ > 0) {
        uint64_t slice_size = read_buffer_.getAvailableSliceCount();
        RawSlice slices[slice_size];
        read_buffer_.getRawSlice(slices, slice_size);

        for (auto s : slices) {
            auto rv = session_.processData(static_cast<const uint8_t*>(s.mem_), s.len_);
            if (rv == -1) {
                logger->error("processData failed {},", fd_);
                // return;
            }
        }

        read_buffer_.drain(read_buffer_.length());
        session_.sendData();
    }

    // not support half-close, so need_close_ == end_stream_end_
    if (result.need_close_ || result.end_stream_read_) {
        closeSocket();
    }
}

void ServerConnection::closeSocket() {
    SPDLOG_TRACE(logger, "closing connection fd={}", fd_);
    // ::close(fd_);
    state_ = network::SocketState::Closed;
    socket_event_.reset();

    mark_closed_(fd_);
}

IoResult ServerConnection::readData(){
    uint64_t bytes_read = 0;
    bool end_stream = false;
    bool need_close = false;

    while(true) {
        int rc = read_buffer_.read(fd_, 65535);
        SPDLOG_TRACE(logger, "read bytes is {}",rc);

        if (rc == 0) {
            end_stream = true;
            break;
        } else if (rc < 0){
            if (errno != EAGAIN) {
                need_close = true;
            }
            break;
        } else {
            bytes_read += rc;
        }
    }

    return {bytes_read, need_close, end_stream};
}

int ServerConnection::onBeginHeaderCallback(nghttp2_session *session, const nghttp2_frame *frame) {
    SPDLOG_TRACE(logger, "start header process... fd={}, stream_id={}", fd_, frame->hd.stream_id);

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
    SPDLOG_TRACE(logger, "fd={} is write-ready", fd_);
    if (write_buffer_.length() == 0) {
        return;
    }

    uint64_t bytes_written = 0;

    // TODO: check connection is active
    do {
        if (write_buffer_.length() == 0) {
            // keep open
            break;
        }

        int rc = write_buffer_.write(fd_);

        if (rc == -1) {
            if (errno == EAGAIN) {
                // keep open
            } else {
                // close
            }

            break;
        } else {
            bytes_written += rc;
        }
    } while(true);

    SPDLOG_TRACE(logger, "Sending data {} bytes fd={}", bytes_written, fd_);
    if (bytes_written > 0) {
        // TODO
    }
}

ssize_t ServerConnection::onSendCallback(const uint8_t* data, const size_t length) {
    SPDLOG_TRACE(logger, "Queueing data {} bytes fd={}", length, fd_);
    Buffer buf { data, length };
    write_buffer_.takeIn(buf);
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

int ServerConnection::onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len) {
    std::cout << "[onDataChunkRecvCallback]\n";
    // Stream* stream = getStream(streama_id);
    // buffer::BufferReader buf {(const char *)data, len};
    // auto encode_flag =  buf.readUINT8();
    // auto plength =  buf.readUINT32();

    // helloworld::HelloRequest request {};
    // std::string s { buf.buffer(), plength };
    // if (!request.ParseFromString(s)) {
    //     std::cout << "error when parsing request protobuf" << std::endl;
    //     return 1;
    // }

    // TODO use response

    // stream->buffer_.add(data, len);
    // TODO
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

    std::map<std::string, std::string> v = {
        {http2::headers::HTTP_STATUS, "200"},
        {http2::headers::CONTENT_TYPE, http2::headers::CONTENT_TYPE_VALUE},
    };

    http2::DataFrame d { stream->stream_id_, true, std::move(v) };
    d.data_ = bufw;

    // XXX: true
    // copy...
    if (session.submitResponse(d) != 0) {
        exit(1);
    }
}

int ServerConnection::onStreamCloseCallback(int32_t stream_id, uint32_t error_code) {
    http2::Stream* stream = session_.getStream(stream_id);

    if (stream) {
        if (stream->remote_end_stream_) {
            SPDLOG_TRACE(logger, "stream={} fd={} is closed by peer", stream_id, fd_);
        }
    }

    // remote stream from streams
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
        SPDLOG_TRACE(logger, "[TODO]Recieved GOAWAY frame fd={}, stream_id={}", fd_, frame->hd.stream_id);
        // handleGoawayFrame()
        break;
    }
    case NGHTTP2_DATA: {
        SPDLOG_TRACE(logger, "Recieved DATA frame fd={}, stream_id={}", fd_, frame->hd.stream_id);
        // handleDataFrame();
        stream->remote_end_stream_ = frame->hd.flags & NGHTTP2_FLAG_END_STREAM;
        sendReply(session_, stream);
        break;
    }
    case NGHTTP2_HEADERS: {
        stream->remote_end_stream_ = frame->hd.flags & NGHTTP2_FLAG_END_STREAM;

        SPDLOG_TRACE(logger, "Recieved HEADERS frame fd={}, stream_id={}", fd_, frame->hd.stream_id);


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
            std::cout << "[Frame Recv] HEADERS NGHTTP2_HCAT_HEADERS \n";
            break;
        }
        default: {
            return 1;
        };
        }
    }
    case NGHTTP2_RST_STREAM: {
        SPDLOG_TRACE(logger, "[TODO] Recieved RST_STREAM frame fd={}, stream_id={}", fd_, frame->hd.stream_id);
        break;
    }
    }

    return 0;
}

ConnectionManager::ConnectionManager(event_base *base):
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

int main(int argc, char **argv) {
    logger->set_level(spdlog::level::trace);

    logger->info("starting server...");

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
    ConnectionManager cm {base};

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))<0) {
        goto err;
    }

    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof(on))<0) {
        goto err;
    }

    listener = evconnlistener_new(base, accept_conn_cb, &cm, LEV_OPT_CLOSE_ON_FREE, -1, fd);

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
