package(default_visibility = ["//visibility:public"])

load("//thirdparty:vega_main.bzl", "vega_copts", "vega_linkopts")

cc_library(
    name = "server",
    srcs = [
        "server.cc",
        "server.hpp"
    ],
    deps = [
        "@thirdparty//:nghttp2",
        ":session_handler",
        ":callback_builder",
        ":stream",
        "//network:socket",
        "//:logger"
    ],
    copts = vega_copts(),
    linkopts = vega_linkopts()
)

cc_library(
    name = "stream",
    srcs = [
        "stream.cc",
        "stream.hpp"
    ],
    deps = [
        "//:logger"
    ],
    copts = vega_copts(),
    linkopts = vega_linkopts()
)

cc_library(
    name = "callback_builder",
    srcs = [
        "callback_builder.hpp"
    ],
    deps = [
        "@thirdparty//:nghttp2",
        ":session_handler"
    ],
    copts = vega_copts(),
    linkopts = vega_linkopts()
)

cc_library(
    name = "session_handler",
    srcs = [
        "session_handler.hpp"
    ],
    deps = [
        "@thirdparty//:nghttp2",
    ],
    copts = vega_copts(),
    linkopts = vega_linkopts()
)
