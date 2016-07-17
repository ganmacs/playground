#!/bin/bash

fail() {
    echo -e -n "\033[0;31m[ERROR]\033[0;39m"
    echo "$1"
    exit 1
}

do_run() {
    echo "$2" | MLISP_TEST=1 ./mlisp > /dev/null
    if [ "$?" -ne 0 ]; then
        echo FAILED
        fail "$error"
    fi

    result=$(echo "$2" | MLISP_TEST=1 ./mlisp 2> /dev/null)
    if [ "$result" != "$3" ]; then
        echo FAILED
        fail "$2 expected, but got $result"
    fi
}

run() {
    echo -n "Testing $1 ... "
    do_run "$@"
    echo
}


run "list" "(+ 1 2 10 1000 100000)" "(+ 1 2 10 1000 100000)"
run "list2" "(+ a bc cde abc10)" "(+ a bc cde abc10)"
run "dot" "(10 . 20)" "(10 . 20)"
run "fun" "(inc 10)" "(inc 10)"
