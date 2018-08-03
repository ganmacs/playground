#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <queue>

namespace http2 {
    enum class FrameType {
        DATA,
        HEADERS,
        PRIORITY,
        RST_STREAM,
        SETTINGS,
    };

    struct Frame {
    public:
        virtual uint32_t streamId() = 0;
        virtual FrameType frameType() = 0;
    };

    struct DataFrame: public Frame {
    public:
        DataFrame(uint32_t id): stream_id_{id} {};
        DataFrame(uint32_t id, bool end_stream);

        uint32_t streamId() override { return stream_id_; }
        FrameType frameType() override { return FrameType::DATA; }

        unsigned char* data_;
        const
        std::map<std::string, std:: string> inner_; // XXX
    private:
        const uint32_t stream_id_;
        const bool end_stream_ { false };
    };

    struct HeadersFrame: public Frame {
    public:
        HeadersFrame(uint32_t id): stream_id_{id} {};
        uint32_t streamId() override { return stream_id_; }
        FrameType frameType() override { return FrameType::HEADERS; }

        std::map<std::string, std:: string> inner_; // XXX
    private:
        uint32_t stream_id_;
        bool end_stream_ { false };
    };

    using FrameQueue = std::queue<Frame>;
};
