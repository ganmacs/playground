package(default_visibility = ["//visibility:public"])

load("//thirdparty:vega_main.bzl", "vega_copts")

cc_library(
    name = "socket",
    srcs = [
        "socket.cc",
        "socket.hpp"
    ],
    deps = [
        "//network:ip",
        "//:logger"
    ],
    copts = vega_copts()
)

cc_library(
    name = "ip",
    srcs = [
        "ip.cc",
        "ip.hpp"
    ],
    deps = [
        "//:logger"
    ],
    copts = vega_copts()
)
