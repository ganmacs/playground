licenses(["notice"])

package(default_visibility = ["//visibility:public"])

load("//thirdparty:vega_main.bzl", "vega_copts", "vega_linkopts")

cc_binary(
    name = "vega",
    srcs = [
        "main.cc",
        "main.hpp"
    ],
    deps = [
        "@thirdparty//:libev",
        ":logger",
        ":server"
    ],
    copts = vega_copts(),
    linkopts = vega_linkopts()
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
    copts = vega_copts(),
    linkopts = vega_linkopts()
)

cc_library(
    name = "ev_loop",
    srcs = [
        "ev_loop.cc",
        "ev_loop.hpp"
    ],
    deps = [
        "@thirdparty//:libev",
        ":logger"
    ],
    copts = vega_copts(),
    linkopts = vega_linkopts()
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
        "//session:server",
        ":logger",
        ":server_connection",
        ":ev_loop"
    ],
    copts = vega_copts(),
    linkopts = vega_linkopts()
)

cc_library(
    name = "server_connection",
    srcs = [
        "server_connection.cc",
        "server_connection.hpp"
    ],
    deps = [
        "//network:socket",
        ":logger"
    ],
    copts = vega_copts(),
    linkopts = vega_linkopts()
)
