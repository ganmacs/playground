def vega_copts(test = False):
    return [
        "-Wall",
        "-Wextra",
        # "-Werror",
        "-Wnon-virtual-dtor",
        "-Woverloaded-virtual",
        "-Wold-style-cast",
        "-std=c++17",
        "-g",
        "-fsanitize=address",
        "-fno-omit-frame-pointer"
    ]

def vega_linkopts(test = False):
    return [
        "-rpath /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/9.1.0/lib/darwin /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/9.1.0/lib/darwin/libclang_rt.asan_osx_dynamic.dylib"
    ]
