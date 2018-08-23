#pragma once

#include <algorithm>
#include <string>
#include <list>
#include <memory>
#include <utility>

#include "nghttp2/nghttp2.h"

#include "hellworld.pb.h"
#include "route_guide.pb.h"

#include "session.hpp"
#include "logger.hpp"
#include "timer.hpp"
#include "socket.hpp"
#include "tcp_server.hpp"
#include "tcp_client.hpp"
#include "socket_event.hpp"
#include "headers.hpp"

namespace network {
    enum class SocketState {
        Open,
        Closing,
        Closed,
    };
}

using markClosedConnection = std::function<void(int)>;

class ServerConnection: public http2::ConnectionHandler {
public:
    ServerConnection(event_base* base, evutil_socket_t fd, markClosedConnection cb);
    ServerConnection* base() { return this; }
    int fd() { return socket_.get()->fd(); }

    // for libevent2 callbacks
    void onSocketEvent(uint32_t events);

    // for nghttp2 callbacks
    ssize_t onSendCallback(const uint8_t* data, const size_t length);
    int onBeginHeaderCallback(nghttp2_session *session, const nghttp2_frame *frame);
    int onHeaderCallback(const nghttp2_frame *frame, std::string name, std::string value);
    int onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len);
    int onFrameRecvCallback(const nghttp2_frame* frame);
    int onFrameSendCallback(const nghttp2_frame* frame);
    int onStreamCloseCallback(int32_t stream_id, uint32_t error_code);

    network::SocketState state_ {network::SocketState::Open};
private:
    void onSocketRead();
    void onSocketWrite();
    void closeSocket();

    markClosedConnection mark_closed_;
    Network::BufferedSocketPtr socket_;

    Event::SocketEventPtr socket_event_;
    http2::Session session_;

    // linked list
    std::list<http2::StreamPtr> streams_;
};

using ServerConnectionPtr = std::unique_ptr<ServerConnection>;

class ConnectionManager: public Tcp::AcceptHandler {     // XXX
public:
    ConnectionManager(event_base *base);
    void registerConnection(const int fd, ServerConnectionPtr&& conn);
    void deleteConnection(const int fd);
    void clearUnavailableConnection();
    void onAccept(int fd) override;

    event_base* base_;
    std::map<int, ServerConnectionPtr> active_connections_; // use abstract class
    Event::TimerPtr connection_cleaner_;
    std::vector<int> unavailable_connections_;
};
