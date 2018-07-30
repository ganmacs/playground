#include "main.hpp"

static Http2Callbacks callbacks {};

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
    std::cout << "[read] target file descriptor " << fd <<  "\n";
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
        // TODO: if EAGAIN, then more data would read.
        std::cout << "[read] " << strerror(errno) <<  "\n";
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
    event_base *base = evconnlistener_get_base(listener);
    std::cout << "[accept_conn_cb] \n";
    ServerConnection *conn = new ServerConnection(base, fd);
}

static void accept_error_cb(struct evconnlistener *listener, void *ctx) {
    struct event_base *base = evconnlistener_get_base(listener);
    int err = EVUTIL_SOCKET_ERROR();
    fprintf(stderr, "Got an error %d (%s) on the listener. "
            "Shutting down.\n", err, evutil_socket_error_to_string(err));

    event_base_loopexit(base, NULL);
}

SocketEvent::SocketEvent(event_base* base, int fd, SocketEventCb cb, uint32_t events): base_{base}, cb_{cb}, fd_{fd} {
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

ServerConnection::ServerConnection(event_base* ebase, evutil_socket_t fd): fd_{fd} {
    std::cout << "[init ServerConnection]\n";
    auto fn = [this](uint32_t events) -> void { onSocketEvent(events); };
    event_ = SocketEventPtr(new SocketEvent(ebase, fd, fn, SocketEventType::Read|SocketEventType::Write));

    nghttp2_session_server_new(&session_, callbacks.callbacks(), base());
    int rc = nghttp2_submit_settings(session_, NGHTTP2_FLAG_NONE, 0, 0);
    if (rc != 0) {
        std::cout << "invalid fd\n";
        exit(1);
    }
}

void ServerConnection::onSocketEvent(uint32_t events) {
    if (fd_ < 0) {
        std::cout << "invalid fd\n";
        return;
    }

    if (events & SocketEventType::Closed) {
        std::cout << "closed\n";
        return;
    }

    if (events & SocketEventType::Read) {
        onSocketRead();
    }

    if (events & SocketEventType::Write) {
        onSocketWrite();
    }
}

void ServerConnection::onSocketRead(){
    std::cout << "[onSocketRead]\n";
    uint64_t rc = readData();
    std::cout << "recv data " << read_buffer_.length() << "|" << rc << " bytes\n";

    uint64_t slice_size = read_buffer_.getAvailableSliceCount();
    RawSlice slices[slice_size];
    read_buffer_.getRawSlice(slices, slice_size);


    for (auto s : slices) {
        // printf("%s\n", static_cast<const uint8_t*>(s.mem_));
        ssize_t rc = nghttp2_session_mem_recv(session_, static_cast<const uint8_t*>(s.mem_), s.len_);
        if (rc != s.len_) {
            std::cout  << "nghttp2_session_mem_recv failed? " << nghttp2_strerror(rc) << "\n";
        }
    }

    read_buffer_.drain(read_buffer_.length());

    sendData();
}

int ServerConnection::sendData() {
    int rv = nghttp2_session_send(session_);
    if (rv != 0) {
        printf("Fatal error: %s", nghttp2_strerror(rv));
        return -1;
    }
    return 0;
}

uint64_t ServerConnection::readData(){
    uint64_t bytes_read = 0;

    while(true) {
        int rc = read_buffer_.read(fd_, 65535);

        if (rc == 0) {
            puts("finish!");
            break;
        } else if (rc < 0){
            // puts("failed?");
            break;
            // exit(1);
        } else {
            bytes_read += rc;
        }
    }

    return bytes_read;
}

// XXX
Stream::Stream(int32_t stream_id):
    stream_id_{stream_id},
    headers_{},
    headers_state_{HeadersStatePtr { new HeadersState() }}
{}

int ServerConnection::onBeginHeaderCallback(nghttp2_session *session, const nghttp2_frame *frame) {
    std::cout << "[onBeginHeaderCall]\n";

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

    StreamPtr stream { new Stream(frame->hd.stream_id) };

    streams_.emplace_front(std::move(stream));

    nghttp2_session_set_stream_user_data(session_, frame->hd.stream_id, streams_.front().get());
    std::cout << "[user data set]\n";
    return 0;
}

void ServerConnection::onSocketWrite(){
    if (write_buffer_.length() == 0) {
        return;
    }
    std::cout << "[onSocketWrite]\n"; // XXX
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

    if (bytes_written > 0) {
        std::cout << "write " << bytes_written << " bytes\n";
    }
}

ssize_t ServerConnection::onSendCallback(const uint8_t* data, const size_t length) {
    std::cout << "[onSendCallback] Send data: " << length <<  " bytes\n";
    Buffer buf { data, length };
    write_buffer_.takeIn(buf);
    return length;
};

int ServerConnection::saveHeader(const nghttp2_frame *frame, std::string name, std::string value) {
    Stream* stream = getStream(frame->hd.stream_id);
    if (!stream) {
        std::cout << "[saveHeader] stream does not exist\n";
        return 0;
    }

    stream->saveHeader(std::move(name), std::move(value));

    // TODO: EHADER size is acceptable
    return 0;
}

Stream* ServerConnection::getStream(int32_t stream_id) {
    auto user_data = nghttp2_session_get_stream_user_data(session_, stream_id);
    return static_cast<Stream*>(user_data);
}

int ServerConnection::onHeaderCallback(const nghttp2_frame *frame, std::string name, std::string value) {
    std::cout << "[onHeaderCallback] " << name << " : " <<  value << " \n";
    Stream* s = getStream(frame->hd.stream_id);

    if (frame->hd.type == NGHTTP2_HEADERS) {
        // if (frame->headers.cat == NGHTTP2_HCAT_RESPONSE || frame->headers.cat == NGHTTP2_HCAT_HEADERS) {
        // std::cout << "[HEADER]:  " << name << " : " <<  value << " \n";
        s->headers_state_->processHeaderField(std::move(name), std::move(value));
        return 0;
        // }
    }

    return 0;
};

namespace GRPC {
    Path::Path(std::string p) {
        std::cout << p << "\n";
        if (p != "" && p[0] == '/') {
            p.erase(p.begin());
        }

        int pos = p.find("/");
        if (pos < -1) {
            // error
        } else {
            service_name_ = p.substr(0, pos-1);
            method_name_ = p.substr(pos + 1, p.length()-1);
        }
    }

    const std::string& Path::MethodName() {
        return method_name_;
    }

    const std::string& Path::ServiceName() {
        return service_name_;
    }
}

// Support request header only now.
void HeadersState::processHeaderField(std::string name, std::string value) {
    if (name == "content-type") {
    } else if (name == ":path")  {
        path_ = GRPC::Path { std::move(value) };
    } else if (name == "schema")  {
        if ((value == "http") || (value == "http2")) {
            schema_ = std::move(value);
        } else {
            // error
        }
    } else if (name == "grpc-encoding") {
        encoding_ = std::move(value);
    } else if (reservedHeader(name) && !whiteListeHeader(name)) {
        return;

    } else {
        // TODO: other header sholud be filtered
        addMetadata(std::move(name), std::move(value));
    }
}

void HeadersState::addMetadata(std::string name, std::string value) {
    // XXX: duplicate name exists...
    metadata_[std::move(name)] = std::move(value);
}

bool HeadersState::whiteListeHeader(const std::string& name) {
    return (name == ":authority" || name == "user-agent");
}

bool HeadersState::reservedHeader(const std::string& name) {
    if (name != "" && name[0] == ':') {
        return true;
    }

    return (name == "content-type" ||
            name == "user-agent"||
            name == "grpc-message-type"||
            name == "grpc-encoding"||
            name == "grpc-message"||
            name == "grpc-status"||
            name == "grpc-timeout"||
            name == "grpc-status-details-bin"||
            name == "te");
}

int ServerConnection::onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len) {
    std::cout << "[onDataChunkRecvCallback]\n";
    // TODO
    return 0;
}

static uint8_t STATUS[8] = ":status";
static uint8_t STATUS_CODE[4] = "200";

void alwaysSuccess(nghttp2_session *session, Stream* stream) {
    const nghttp2_nv hdrs {STATUS, STATUS_CODE, sizeof(STATUS)-1, sizeof(STATUS_CODE)-1, 0};
    puts("Always success");
    nghttp2_submit_response(session, stream->stream_id_, &hdrs, 1, nullptr);
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
    std::cout << "[onFrameRecvCallback]" << frame->hd.type << "\n";
    Stream* stream = getStream(frame->hd.stream_id);

    switch(frame->hd.type) {
    case NGHTTP2_GOAWAY: {
        std::cout << "[Frame Recv] GOAWAY\n";
        break;
    }
    case NGHTTP2_DATA: {
        std::cout << "[Frame Recv] DATA\n";
        stream->end_stream_ = frame->hd.flags & NGHTTP2_FLAG_END_STREAM;
        break;
    }
    case NGHTTP2_HEADERS: {
        stream->end_stream_ = frame->hd.flags & NGHTTP2_FLAG_END_STREAM;

        switch (frame->headers.cat) {
        case NGHTTP2_HCAT_RESPONSE: {
            std::cout << "[Frame Recv] HEADERS NGHTTP2_HCAT_RESPONSE \n";
            break;
        }
        case NGHTTP2_HCAT_REQUEST: {
            std::cout << "[Frame Recv] HEADERS NGHTTP2_HCAT_REQUEST \n";
            alwaysSuccess(session_, stream);
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
        std::cout << "[Frame Recv] NGHTTP2_RST_STREAM\n";
        break;
    }
    }
    return 0;

}

int Stream::saveHeader(std::string name, std::string value) {
    return 0;
}

Http2Callbacks::Http2Callbacks() {
    nghttp2_session_callbacks_new(&callbacks_);

    // nghttp2_session_callbacks_set_on_frame_send_callback(
    //     callbacks_, [](nghttp2_session*, const nghttp2_frame* frame, void* user_data) -> int {
    //         return static_cast<ConnectionImpl*>(user_data)->onFrameSend(frame);
    //     });

    nghttp2_session_callbacks_set_send_callback(
       callbacks_,
       [](nghttp2_session*, const uint8_t* data, size_t length, int, void* user_data) -> ssize_t {
           return static_cast<ServerConnection*>(user_data)->onSendCallback(data, length);
       }
    );

    nghttp2_session_callbacks_set_on_begin_headers_callback(
       callbacks_,
       [](nghttp2_session* session, const nghttp2_frame *frame, void *user_data) -> int {
           return static_cast<ServerConnection*>(user_data)->onBeginHeaderCallback(session, frame);
       }
    );

    nghttp2_session_callbacks_set_on_data_chunk_recv_callback(
      callbacks_,
      [](nghttp2_session*, uint8_t, int32_t stream_id, const uint8_t* data, size_t len, void* user_data) -> int {
        return static_cast<ServerConnection*>(user_data)->onDataChunkRecvCallback(stream_id, data, len);
      });

    nghttp2_session_callbacks_set_on_frame_recv_callback(
      callbacks_, [](nghttp2_session*, const nghttp2_frame* frame, void* user_data) -> int {
        return static_cast<ServerConnection*>(user_data)->onFrameRecvCallback(frame);
      });

    nghttp2_session_callbacks_set_on_header_callback(
      callbacks_,
      [](nghttp2_session*, const nghttp2_frame* frame, const uint8_t* raw_name, size_t name_length,
         const uint8_t* raw_value, size_t value_length, uint8_t, void* user_data) -> int {
          std::string name { raw_name, raw_name+name_length };
          std::string value { raw_value, raw_value+value_length };
          return static_cast<ServerConnection*>(user_data)->onHeaderCallback(frame, std::move(name), std::move(value));
      });
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
