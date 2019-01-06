package(default_visibility = ["//visibility:public"])

load("//thirdparty:vega_main.bzl", "vega_copts", "vega_linkopts")

cc_library(
    name = "reader",
    srcs = [
        "reader.cc",
        "reader.hpp"
    ],
    deps = [
        "//:logger",
    ],
    copts = vega_copts(),
    linkopts = vega_linkopts()
)
