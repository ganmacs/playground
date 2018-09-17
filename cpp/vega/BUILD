licenses(["notice"])

package(default_visibility = ["//visibility:public"])

load("//thirdparty:vega_main.bzl", "vega_copts")

cc_binary(
    name = "vega",
    srcs = [
        "main.cc",
        "main.hpp"
    ],
    deps = [
        "@thirdparty//:libev",
        "@thirdparty//:nghttp2",
        ":logger",
        ":server"
    ],
    copts = vega_copts()
)

cc_library(
    name = "logger",
    srcs = [
        "logger.cc",
        "logger.hpp"
    ],
    deps = [
        "@spdlog//:spdlog"
    ],
    copts = vega_copts()
)

cc_library(
    name = "server",
    srcs = [
        "server.cc",
        "server.hpp"
    ],
    deps = [
        "@thirdparty//:libev",
        "//network:socket",
        ":logger"
    ],
    copts = vega_copts()
)
