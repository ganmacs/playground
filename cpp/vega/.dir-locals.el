;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

((c++-mode . ((flycheck-clang-warnings . ("no-pragma-once-outside-header" "no-noexcept-type"))
              (flycheck-clang-include-path . ("./bazel-vega/external/thirdparty/thirdparty_build/include"
                                              "./../bazel-vega/external/thirdparty/thirdparty_build/include"
                                              "./bazel-vega/external/spdlog/include"
                                              "./../bazel-vega/external/spdlog/include"))
              ;; (flycheck-gcc-language-standard . "c++17")
              ;; (flycheck-clang-language-standard . "c++17")
              )))
