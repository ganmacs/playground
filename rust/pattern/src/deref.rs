// this is a usage of deref(*) operator

use std::ops::Deref;

type Width = usize;

struct DisplayWidth(usize);

impl Deref for DisplayWidth {
    type Target = usize;

    fn deref<'a>(&'a self) -> &'a Self::Target {
        &self.0
    }
}

#[derive(Debug)]
struct Box {
    w: Width
}

pub fn run() {
    let width: Width = 1;
    let dwidth = DisplayWidth(10);

    println!("{:?}", Box { w: width });
    println!("{:?}", Box { w: *dwidth });
}
