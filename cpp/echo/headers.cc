#include "headers.hpp"

namespace http2 {
    nghttp2_nv make_nghttp2_nv2(const char *name, const char *value, size_t nameLength, size_t valueLength, std::uint8_t flags) {
        return nghttp2_nv {
            const_cast<std::uint8_t *>(reinterpret_cast<const std::uint8_t*>(name)),
            const_cast<std::uint8_t *>(reinterpret_cast<const std::uint8_t*>(value)),
            nameLength, valueLength, flags
            };
    }

    nghttp2_nv make_nghttp2_nv(const std::string &name, const std::string &value, bool noIndex) {
        return make_nghttp2_nv2(name.data(), value.data(), name.length(), value.length(),
                                noIndex ? NGHTTP2_NV_FLAG_NO_INDEX : NGHTTP2_NV_FLAG_NONE);
    }

    std::vector<nghttp2_nv> makeHeaderNv(const HeaderMap &headers) {
        auto nvs = std::vector<nghttp2_nv>();
        nvs.reserve(headers.size());

        for (auto &h : headers) {
            nvs.emplace_back(make_nghttp2_nv(h.first, h.second, true));
        }

        return nvs;
    }
}
