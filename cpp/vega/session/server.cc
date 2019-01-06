#include "server.hpp"

namespace vega {
    namespace session {
        BaseSession::BaseSession(vega::network::AcceptedSocketPtr socket): socket_(socket) {};

        int BaseSession::sendSettings(http2Settings settings) noexcept {
            std::vector<nghttp2_settings_entry> iv;

            if (settings.max_concurrent_streams_ == NGHTTP2_INITIAL_MAX_CONCURRENT_STREAMS) {
                // TODO: check max
                iv.push_back({NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS, settings.max_concurrent_streams_});
            }

            if (iv.empty()) {
                return nghttp2_submit_settings(session_, NGHTTP2_FLAG_NONE, 0, 0);
            } else {
                return nghttp2_submit_settings(session_, NGHTTP2_FLAG_NONE, &iv[0], iv.size());
            }
        }

        ssize_t BaseSession::memRecv(const uint8_t* data, ssize_t len) noexcept {
            ssize_t rv = nghttp2_session_mem_recv(session_, data, len);
            if (rv != len) {
                logger->error("Fatal error nghttp2_session_mem_recv: {}", nghttp2_strerror(rv));
                return -1;
            }
            return rv;
        }

        Stream *BaseSession::getStreamData(const uint32_t stream_id) noexcept {
            auto user_data = nghttp2_session_get_stream_user_data(session_, stream_id);
            return static_cast<Stream*>(user_data);
        }

        int BaseSession::setNewStream(const uint32_t stream_id) noexcept {
            StreamPtr stream { new Stream(stream_id) };
            streams_.emplace_front(std::move(stream));
            return setStreamData(stream_id, streams_.front().get());
        }

        int BaseSession::setStreamData(const uint32_t stream_id, Stream *stream) noexcept {
            auto rv = nghttp2_session_set_stream_user_data(session_, stream_id, stream);
            if (rv != 0) {
                logger->error("set stream failed: {}", nghttp2_strerror(rv));
                return -1;
            }
            return 0;
        }

        Server::Server(vega::network::AcceptedSocketPtr socket): session_(std::make_unique<BaseSession>(socket)) {
            nghttp2_session_server_new(session_->base(), callback_builder.build(), static_cast<void*>(this));

            if (session_->sendSettings({ 100 }) == -1) {
                logger->error("Failed sending Setting frame");
                abort();
            }
        }

        // ssize_t Server::onSendCallback(const uint8_t *data, size_t length) {
        ssize_t Server::onSendCallback(const uint8_t *, size_t ) {
            return 0;
        }

        int Server::onBeginHeaderCallback(nghttp2_session*, const nghttp2_frame *frame) {
            SPDLOG_TRACE(logger, "BeginHeader fd={}, stream_id={}", session_->fd(), frame->hd.stream_id);
            if (session_->getStreamData(frame->hd.stream_id) == nullptr) {
                return session_->setNewStream(frame->hd.stream_id);
            }

            return 0;
        }

        // int Server::onDataChunkRecvCallback(int32_t stream_id, const uint8_t* data, size_t len) {
        int Server::onDataChunkRecvCallback(int32_t , const uint8_t* , size_t) {
            return 0;
        }

        // int Server::onFrameRecvCallback(const nghttp2_frame* frame) {
        int Server::onFrameRecvCallback(const nghttp2_frame* ) {
            return 0;
        }

        // int Server::onFrameSendCallback(const nghttp2_frame* frame) {
        int Server::onFrameSendCallback(const nghttp2_frame*) {
            return 0;
        }

        int Server::onHeaderCallback(const nghttp2_frame* frame, std::string name, std::string value) {
            SPDLOG_TRACE(logger, "{} => {}", name, value);
            // Stream* s = session_->getStreamData(frame->hd.stream_id);
            return 0;
        }

        // int Server::onStreamCloseCallback(int32_t stream_id, uint32_t error_code) {
        int Server::onStreamCloseCallback(int32_t , uint32_t ) {
            return 0;
        }

        ssize_t Server::onRead(const uint8_t *data, ssize_t len) noexcept {
            // want_read?
            return session_->memRecv(data, len);
        }
    }
}
