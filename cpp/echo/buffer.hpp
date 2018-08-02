#pragma once

#include <iostream>
#include <string>

namespace buffer {
    class BufferReader {
    public:
        BufferReader(const char *data, const size_t len);
        const uint8_t readUINT8();
        const uint32_t readUINT32();
        const size_t restLength();
        char *buffer();

        const size_t len_;
        const char *data_;
        size_t pos_ {0};
    private:
        const char *read(size_t size);
    };

    class BufferWriter {
    public:
        BufferWriter();
        std::string& inner() { return buf_; }
        size_t length() { return buf_.length(); }
        void putUINT32(uint32_t v);
        void putUINT8(uint8_t v);
        void append(std::string v);
        size_t write_to(void *dest);


    private:
        std::string buf_;
        size_t pos_ {0};
    };
}
