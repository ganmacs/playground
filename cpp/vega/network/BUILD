package(default_visibility = ["//visibility:public"])

load("//thirdparty:vega_main.bzl", "vega_copts")

cc_library(
    name = "socket",
    srcs = [
        "socket.cc",
        "socket.hpp"
    ],
    deps = [
        "@spdlog//:spdlog"
    ],
    copts = vega_copts()
)
