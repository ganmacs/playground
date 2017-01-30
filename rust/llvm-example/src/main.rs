extern crate llvm_example;

use llvm_example::*;

use llvm_example::node::*;
fn main() {
    let v = assgn("foo", iint(1));
    let i = ifexpr(aref("foo"),
                   assgn("foo", iint(1000)),
                   assgn("foo", iint(1)));
    let i2 = aref("foo");
    // compile(vec![v, i, i2]);

    // let i = ifexpr(aref("foo"), assgn("foo", iint(1000)), assgn("foo", iint(1)));
    // let i2 = aref("foo");
    compile(vec![v, i, i2]);
}
