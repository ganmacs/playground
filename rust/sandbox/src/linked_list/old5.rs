#[derive(Debug)]
struct A {
    n: usize,
}

#[derive(Debug)]
struct B {
    a: Box<A>,
    b: *mut A,
}

impl Drop for A {
    fn drop(&mut self) {
        println!("Drop {:?}", self);
    }
}

impl Drop for B {
    fn drop(&mut self) {
        println!("Drop {:?}", self);
        unsafe {
            Box::from_raw(self.b);
        }
    }
}

fn a() -> B {

    let b = {
        let v = A { n: 10 };
        let a = A { n: 9 };
        let mut k = Box::new(a);
        let b = B {
            a: Box::new(v),
            b: Box::into_raw(k),
        };
        b
    };

    println!("-----------------------------{:?}--", b);
    b
}

pub fn main() {
    let b = a();
    println!("{:?}", b.a);

    println!("{:?}", b);
}
