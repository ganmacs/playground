#pragma once

#include <cstdint>
#include <string>
#include <list>
#include <unordered_map>

#include "session.hpp"
#include "headers.hpp"
#include "frame.hpp"

namespace http2 {
    class Session;

    struct GrpcPath {
    public:
        GrpcPath() {};
        GrpcPath(std::string service_name,  std::string method_name):
            service_name_{service_name}, method_name_{method_name} {};

        GrpcPath& operator=(GrpcPath &&rhs) noexcept {
            this->method_name_ = std::move(rhs.method_name_);
            this->service_name_ = std::move(rhs.service_name_);
            return *this;
        }

        std::string service_name_;
        std::string method_name_;
    };

    enum class StreamStatus {
        StreamActive,
        // half-closed and send END_STREAM
        StreamWriteDone,
        // half-closed and recv END_STREAM
        StreamReadDone,
        StreamClose,
    };

    class HeadersState {
    public:
        HeadersState() {};

        // return errro?
        bool reservedHeader(const std::string& name);
        bool whiteListeHeader(const std::string& name);
        void processHeaderField(std::string name, std::string value);
        void addMetadata(std::string name, std::string value);
        std::unordered_map<std::string, std::string> metadata_;

        GrpcPath path_;
        std::string encoding_;
        std::string schema_;
    };

    // using HeadersStatePtr = std::unique_ptr<HeadersState>;

    class Stream {
    public:
        Stream(int32_t stream_id);
        Stream() {};

        ssize_t sendMsg(DataFramePtr d, http2::Session &session);
        ssize_t sendMsg2(http2::Session &session);
        ssize_t sendRespMsg(DataFramePtr d, http2::Session &session);

        int32_t stream_id_{-1};
        HeadersState headers_state_;

        bool remote_end_stream_ {false};
        bool local_end_stream_ {false};
        StreamStatus stream_status_ {StreamStatus::StreamActive};
        std::list<DataFramePtr> item_list_;
        bool sending_{false};
        bool first_sent_{false};
        bool blocking_{false};
    };

    using StreamPtr = std::shared_ptr<Stream>;

    int grpc_path_build(GrpcPath& v , std::string p);
}
