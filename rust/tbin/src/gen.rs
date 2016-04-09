use std::fmt::Debug;

trait HaveArea  {
    fn area(&self) -> f64;
}

#[derive(Debug)]
struct Foo {
    length: f64,
    width: f64,
}

impl HaveArea for Foo {
    fn area(&self) -> f64 { self.length * self.width }
}

fn print_debug<T: Debug>(f: &T) {
    println!("{:?}", f);
}

fn main() {
    let f = Foo { length: 100.0, width: 50.0 };
    // let b = Bar { length: 10, width: 5 };
    print_debug(&f);
}
