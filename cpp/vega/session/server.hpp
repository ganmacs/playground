#pragma once

#include <string>
#include <list>

#include <nghttp2/nghttp2.h>

#include "../network/socket.hpp"
#include "session_handler.hpp"
#include "callback_builder.hpp"
#include "../logger.hpp"
#include "stream.hpp"

namespace vega {
    namespace session {
        struct http2Settings {
            uint32_t max_concurrent_streams_{NGHTTP2_INITIAL_MAX_CONCURRENT_STREAMS};
        };

        class BaseSession {
        public:
            BaseSession(vega::network::AcceptedSocketPtr socket);

            nghttp2_session **base() { return &session_; }
            // ssize_t
            int sendSettings(http2Settings settings) noexcept;
            ssize_t memRecv(const uint8_t* data, ssize_t len) noexcept;

            Stream *getStreamData(const uint32_t stream_id) noexcept;
            int setNewStream(uint32_t stream_id) noexcept;

            int fd() { return socket_->fd(); }

        private:
            nghttp2_session *session_;
            std::list<StreamPtr> streams_;
            network::AcceptedSocketPtr socket_;

            // only server?
            int setStreamData(const uint32_t stream_id, Stream *stream) noexcept;
        };

        using BaseSessionPtr = std::unique_ptr<BaseSession>;

        class Server : public SessionHandler {
        public:
            Server(network::AcceptedSocketPtr socket);

            ssize_t onSendCallback(const uint8_t *data, size_t length);
            int onBeginHeaderCallback(nghttp2_session* session, const nghttp2_frame *frame);
            int onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len);
            int onFrameRecvCallback(const nghttp2_frame* frame);
            int onFrameSendCallback(const nghttp2_frame* frame);
            int onHeaderCallback(const nghttp2_frame* frame, std::string name, std::string value);
            int onStreamCloseCallback(int32_t stream_id, uint32_t error_code);

            // delegation
            ssize_t onRead(const uint8_t *data, ssize_t len) noexcept;

        private:
            BaseSessionPtr session_;
        };

        using ServerPtr = std::unique_ptr<Server>;
    }
}
