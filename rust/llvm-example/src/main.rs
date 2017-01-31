extern crate llvm_example;

use llvm_example::*;
use llvm_example::node::*;

fn test1() {
    let v1 = assgn("foo", iint(11));
    let v3 = assgn("foo", sub(aref("foo"), iint(10)));
    let i = ifexpr(aref("foo"),
                   assgn("foo", iint(1000)),
                   assgn("foo", iint(10)));
    let ret = aref("foo");

    compile(vec![v1, v3, i, ret]);
}

fn test2() {
    unsafe {
        codegen::playground();
    }
}

fn main() {
    // test1()
    test2()
}
