#pragma once

#include "stream.hpp"

namespace http2 {
    int grpc_path_build(GrpcPath& v , std::string p) {
        if (p != "" && p[0] == '/') {
            p.erase(p.begin());
        }

        auto pos = p.find("/");
        if (pos == std::string::npos) {
            // invalid path type
            return -1;
        } else {
            v = { p.substr(0, pos-1), p.substr(pos + 1, p.length()-1) };
            return 0;
        }
    }

    // Support request header only now.
    void HeadersState::processHeaderField(std::string name, std::string value) {
        if (name == "content-type") {

        } else if (name == http2::headers::PATH)  {

            grpc_path_build(path_, std::move(value)); // TODO: check result
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

    Stream::Stream(int32_t stream_id): stream_id_{stream_id} {}
}
