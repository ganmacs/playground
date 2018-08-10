#pragma once

#include <cstdint>
#include <string>
#include <map>

namespace http2 {
    // enum class FrameType {
    //     DATA,
    //     HEADERS,
    //     PRIORITY,
    //     RST_STREAM,
    //     SETTINGS,
    // };

    // struct Frame {
    // public:
    //     virtual int32_t streamId() = 0;
    //     virtual FrameType frameType() = 0;
    // };

    struct DataFrame {
    public:
        DataFrame(int32_t id, bool end_stream, std::map<std::string, std::string> headers);
        DataFrame(int32_t id, bool end_stream);
        DataFrame(int32_t id);

        // DataFrame(DataFrame &&a) noexcept {};


        // int32_t streamId() { return stream_id_; }
        // FrameType frameType() override { return FrameType::DATA; }

        void* data_;
        const int32_t stream_id_;
        const bool end_stream_ { false };
        std::map<std::string, std::string> hdrs_; // XXX

    private:
    };

    // struct HeadersFrame: public Frame {
    // public:
    //     HeadersFrame(int32_t id): stream_id_{id} {};
    //     int32_t streamId() override { return stream_id_; }
    //     FrameType frameType() override { return FrameType::HEADERS; }

    //     std::map<std::string, std:: string> inner_; // XXX
    // private:
    //     const int32_t stream_id_;
    //     bool trailer_ { false };
    //     bool end_stream_ { false };
    // };

    using DataFramePtr = std::shared_ptr<DataFrame>;
};