licenses(["notice"])

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "vega",
    srcs = ["main.cc"],
    copts = [
        "-std=c++17",
        "-fsanitize=address",
        "-fno-omit-frame-pointer",
        "-Wall",
        "-Werror",
        "-U_FORTIFY_SOURCE"
    ],
    linkopts = [
        # only for macos
        "-rpath /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/9.1.0/lib/darwin /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/9.1.0/lib/darwin/libclang_rt.asan_osx_dynamic.dylib"
    ]
)
