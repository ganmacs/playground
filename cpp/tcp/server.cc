#include "server.hpp"

#include <sys/socket.h>
#include <sys/types.h>

struct event_base;
extern "C" {
    void event_base_free(event_base*);
}

static Http2Callbacks callbacks {};

// static void dummyHttp(int fd)  {
//     std::string header {"HTTP1.1 200 OK\nContent-Type: text/plain\n\nbody"};
//     ::write(fd, header.c_str(), header.size());
// }

int Buffer::add(const void* data, uint64_t size) {
    return evbuffer_add(buffer_, data, size);
}

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

    return -1;
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

Http2Callbacks::Http2Callbacks() {
    nghttp2_session_callbacks_new(&callbacks_);

    nghttp2_session_callbacks_set_send_callback(
       callbacks_,
       [](nghttp2_session*, const uint8_t* data, size_t length, int, void* user_data) -> ssize_t {
           return static_cast<ServerConnection*>(user_data)->onSendCallback(data, length);
       });
}

void ServerConnection::sessionRecv(Buffer& buf) {
    std::cout << "[sessionRecv] recv data :" << buf.length() <<  " bytes\n";
    uint64_t slice_size = buf.getAvailableSliceCount();
    RawSlice slices[slice_size];
    buf.getRawSlice(slices, slice_size);

    for (auto s : slices) {
        ssize_t rc = nghttp2_session_mem_recv(session_, static_cast<const uint8_t*>(s.mem_), s.len_);
        if (rc != s.len_) {
            throw "nghttp2_session_mem_recv failed";
        }
    }

    buf.drain(buf.length());
}

ServerConnection::ServerConnection(Server* server, evutil_socket_t fd) {
    std::cout << "[ServerConnection]\n";
    // printf("%d\n", fd);
    // bufferevent_ = bufferevent_socket_new(server->eventBase(), fd, BEV_OPT_CLOSE_ON_FREE);
    // bufferevent_enable(bufferevent_, EV_READ | EV_WRITE);
    // bufferevent_setcb(bufferevent_, readCallback, writeCallback, eventCallback, this);

    nghttp2_session_server_new(&session_, callbacks.callbacks(), base());
}

void ServerConnection::read(bufferevent* buf) {
    Buffer buffer { bufferevent_get_input(buf) };
    sessionRecv(buffer);
}

ssize_t ServerConnection::onSendCallback(const uint8_t* data, const size_t length) {
    std::cout << "[onSendCallback] Send data :" << length <<  " bytes\n";
    Buffer buf { data, length };
    connection_.write(buf);
    return length;
};

// callback for evconnlistener_new
void Server::listenCallback(evconnlistener*, evutil_socket_t fd, sockaddr* remote_addr, int remote_addr_len, void* arg) {
    Server* server = static_cast<Server*>(arg);
    printf("received %d %d\n", fd, server->fd());
    ServerConnection sc { server, fd };

    // uint64_t bytes_read = 0;
    // while(true) {
    //     int rc = conn.buffer().read(fd, 65535);

    //     if (rc == 0) {
    //         puts("finish!");
    //         break;
    //     } else if (rc < 0){
    //         puts("failed?");
    //         break;
    //         // exit(1);
    //     } else {
    //         bytes_read += rc;
    //     }
    // }

    // dummyHttp(fd);
    // close(fd);

    puts("finish!!!");
    // close(fd);
}

int Server::setup(int port) {
    if (bind(port)< 0) {
        printf("failed binding\n");
        return -1;
    }
    evconnlistener_new(base_, listenCallback, this, 0, -1, s_.fd());
    return 1;
}

Server::Server(int fd) : base_{ event_base_new() }, s_{fd} {
    int on = 1;
    int rc = setsockopt(s_.fd(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (rc) {
        s_.close();
        printf( "rc is -1\n");
    }
}

int main(int argc, char *argv[])
{
    Server s { socket(AF_INET, SOCK_STREAM, 0) };
    if (s.setup(3000) < 0) {
        printf("failed" );
    }
    s.start();
    return 0;
}
