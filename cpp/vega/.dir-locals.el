;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

((c++-mode
  (flycheck-clang-include-path . ("/opt/brew/include" "/opt/brew/Cellar/protobuf/3.5.1_1/include"))
  ;; (flycheck-gcc-language-standard . "c++17")
  ;; (flycheck-clang-language-standard . "c++17")
  (flycheck-clang-warnings . ("no-pragma-once-outside-header" "no-noexcept-type"))
  ))
