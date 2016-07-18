#!/bin/bash

fail() {
    echo -e -n "\033[0;31m[ERROR] \033[0;39m"
    echo "$1"
    exit 1
}

do_run() {
    # echo "$2" | ./mlisp > /dev/null
    echo "$2" | ./mlisp
    if [ "$?" -ne 0 ]; then
        echo FAILED
        fail "$error"
    fi

    result=$(echo "$2" | ./mlisp 2> /dev/null)
    if [ "$result" != "$3" ]; then
        echo FAILED
        fail "$3 expected, but got $result"
    fi
}

run() {
    echo -n "Testing $1 ... "
    do_run "$@"
    echo
}

parse_run() {
    MLISP_PARSE_TEST=1 run "$@"
}

eval_run() {
    MLISP_EVAL_TEST=1 run "$@"
}

# == parse test ==
parse_run "list" "(+ 1 2 10 1000 100000)" "(+ 1 2 10 1000 100000)"
parse_run "list2" "(+ a bc cde abc10)" "(+ a bc cde abc10)"
parse_run "dot" "(10 . 20)" "(10 . 20)"
parse_run "fun" "(inc 10)" "(inc 10)"

# == eval test ==
eval_run add "(+ 1 2)" 3
eval_run add_3_args "(+ 1 2 10)" 13
eval_run minus "(- 2 1)" 1
