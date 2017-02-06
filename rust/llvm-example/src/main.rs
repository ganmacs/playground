extern crate llvm_example;

use llvm_example::*;
use llvm_example::node::*;
use std::env;

fn test() {
    let v1 = assgn("foo", iint(11));
    let v3 = assgn("foo", sub(aref("foo"), iint(10)));
    let i = ifexpr(aref("foo"),
                   assgn("foo", iint(1000)),
                   assgn("foo", iint(10)));
    let ret = aref("foo");

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
