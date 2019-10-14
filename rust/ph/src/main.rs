use std::marker::PhantomData;

enum Preparing {} // <--- struct で定義してもよい
enum Ready {} // <-/

struct Something<S> {
    _status: PhantomData<S>,
}

impl Something<Preparing> {
    pub fn new() -> Self {
        Something::<Preparing> {
            _status: PhantomData,
        }
    }

    pub fn prepare(&self) -> Something<Ready> {
        Something::<Ready> {
            _status: PhantomData,
        }
    }
}

impl Something<Ready> {
    pub fn hello(&self) {
        println!("{:?}", "hello");
    }
}

fn main() {
    // println!("Hello, world!");

    let v = Something::new();
    v.prepare().hello();
}
