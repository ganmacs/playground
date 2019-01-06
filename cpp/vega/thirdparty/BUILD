package(default_visibility = ["//visibility:public"])

cc_library(
    name = "libev",
    srcs = ["thirdparty_build/lib/libev.a"],
    hdrs = [
        "thirdparty_build/include/ev.h",
        "thirdparty_build/include/ev++.h",
        "thirdparty_build/include/event.h",
    ],
    includes = ["thirdparty_build/include"],
)

cc_library(
    name = "nghttp2",
    srcs = ["thirdparty_build/lib/libnghttp2.a"],
    hdrs = glob(["thirdparty_build/include/nghttp2/*.h"]),
    includes = ["thirdparty_build/include"],
)
