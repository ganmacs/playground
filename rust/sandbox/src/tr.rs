use std::fmt::Debug;

trait A {
    fn foo(&self) {
        println!("-------------------------------");
    }
}

#[derive(Debug)]
struct B;

impl A for B {}

pub fn run() {
    let b = B {};
    pa(b);
}

fn pa<S>(a: S)
    where S: A + Debug
{
    a.foo();
    a.foo();
    a.foo();
    a.foo();

    println!("{:?}", a);
}
