licenses(["notice"])

package(default_visibility = ["//visibility:public"])

load("//thirdparty:vega_main.bzl", "envoy_copts")

cc_binary(
    name = "vega",
    srcs = [
        "main.cc",
        "main.hpp"
    ],
    deps = [
        "@thirdparty//:libev",
        "@thirdparty//:nghttp2",
        "@spdlog//:spdlog"
    ],
    copts = envoy_copts()
)
