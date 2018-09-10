licenses(["notice"])

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "vega",
    srcs = [
        "main.cc",
        "main.hpp"
    ],
    deps = [
        "@thirdparty//:libev",
        "@thirdparty//:nghttp2"
    ]
)
