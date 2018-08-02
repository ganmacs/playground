#pragma once

#include "buffer.hpp"

namespace buffer {
    inline uint32_t decodeUINT32BE(char *data) {
        return ((static_cast<uint32_t>(static_cast<unsigned char>(data[3])))
                | (static_cast<uint32_t>(static_cast<unsigned char>(data[2])) << 8)
                | (static_cast<uint32_t>(static_cast<unsigned char>(data[1])) << 16)
                | (static_cast<uint32_t>(static_cast<unsigned char>(data[0])) << 24));
    }

    inline void encodeUINT32BE(char *buf, uint32_t v) {
        buf[0] = v & 0xff;
        buf[1] = (v >> 8) & 0xff;
        buf[2] = (v >> 16) & 0xff;
        buf[3] = (v >> 24) & 0xff;
    }

    BufferWriter::BufferWriter() {}

    void BufferWriter::putUINT32(uint32_t v) {
        char buf[sizeof(uint32_t)];
        encodeUINT32BE(buf, v);
        pos_ += sizeof(uint32_t);
        buf_.append(buf);
    }

    void BufferWriter::putUINT8(uint8_t v) {
        char buf[sizeof(uint8_t)];
        buf[0] = v;
        pos_ += sizeof(uint8_t);
        buf_.append(buf);
    }

    void BufferWriter::append(std::string v) {
        pos_ += v.length();
        buf_.append(v);
    }

    const size_t MAX_WRITE_LIMIT = 1024;

    size_t BufferWriter::write_to(void *dest) {
        if (pos_ <= 0) {
            return 0;
        }
        auto write_bytes = std::min(MAX_WRITE_LIMIT, pos_);
        std::memcpy(dest, (char *)buf_.c_str(), write_bytes);
        pos_ -= write_bytes;
        return write_bytes;
    }

    BufferReader::BufferReader(const char* data, const size_t len): len_{len} , data_{data} {}

    char *BufferReader::buffer() {
        return (char *)data_ + pos_;
    }

    const size_t BufferReader::restLength() {
        assert(len_ > pos_);
        return len_ - pos_;
    }

    const char *BufferReader::read(size_t size) {
        if (len_ > pos_ + size) {
            const char *v = (data_ + pos_);
            pos_ += size;
            return v;
        } else {
            assert(len_ > pos_ + size);
        }
    }

    const uint32_t BufferReader::readUINT32() {
        // read(sizeof(uint32_t));
        auto size = sizeof(uint32_t);

        if (len_ > pos_ + size) {
            // auto v = *(uint32_t*)(data_ + pos_);
            auto v = decodeUINT32BE((char *)data_ + pos_);
            pos_ += size;
            return v;
        } else {
            assert(len_ > pos_ + size);
            return 1;               // unreachable
        }
    }

    const uint8_t BufferReader::readUINT8() {
        auto size = sizeof(uint8_t);

        if (len_ > pos_ + size) {
            const uint8_t v = static_cast<uint8_t>(data_[pos_]);
            pos_ += size;
            return v;
        } else {
            assert(len_ > pos_ + size);
            return 1;               // unreachable
        }
    }
}
