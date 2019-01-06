package(default_visibility = ["//visibility:public"])

load("//thirdparty:vega_main.bzl", "vega_copts", "vega_linkopts")

cc_library(
    name = "network",
    srcs = ["network.hpp"],
    deps = [
        "//:logger"
    ],
    copts = vega_copts(),
    linkopts = vega_linkopts()
)

cc_library(
    name = "socket",
    srcs = [
        "socket.cc",
        "socket.hpp"
    ],
    deps = [
        "//network:ip",
        "//network:network"
    ],
    copts = vega_copts(),
    linkopts = vega_linkopts()
)

cc_library(
    name = "ip",
    srcs = [
        "ip.cc",
        "ip.hpp"
    ],
    deps = [
        "//network:network"
    ],
    copts = vega_copts(),
    linkopts = vega_linkopts()
)
