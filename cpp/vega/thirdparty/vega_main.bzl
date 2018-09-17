def vega_copts(test = False):
    return [
        "-Wall",
        "-Wextra",
        "-Werror",
        "-Wnon-virtual-dtor",
        "-Woverloaded-virtual",
        "-Wold-style-cast",
        "-std=c++14",
        "-stdlib=libc++",
        # "-g",
        # "-fsanitize=address",
        # "-fno-omit-frame-pointer",
    ]
