extern crate llvm_example;

use llvm_example::*;
use llvm_example::node::*;
use std::env;

fn test() {
    let v1 = assign("foo", inum(11));
    let v3 = assign("foo", sub(refe("foo"), inum(10)));
    let i = ifexpr(refe("foo"),
                   assign("foo", inum(1000)),
                   assign("foo", inum(10)));
    let ret = refe("foo");

    compile(vec![v1, v3, i, ret]);
}

fn main() {
    let args: String = env::args().skip(1).collect();
    match args.as_ref() {
        "0" => test(),
        "1" => unsafe { llvm1::run() },
        "2" => unsafe { llvm2::run() },
        "3" => unsafe { llvm3::run() },
        "4" => unsafe { llvm4::run() },
        _ => test(),
    }
}
