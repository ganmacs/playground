use std::io::{BufReader, Read, Write};
use std::io::Cursor;
use std::sync::Arc;

pub fn main() {
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
}

struct A(Arc<BufReader<Cursor<Vec<u8>>>>);

impl A {
    pub fn create(&self) -> A {
        A(self.0.clone())
    }

    pub fn read(&mut self) {
        let mut v = vec![1; 10];
        self.0.read_exact(&mut v);
    }
}

fn test1() {
    let mut buff = Cursor::new(vec![1; 15]);
    let mut b = BufReader::new(buff);
    let mut a = A(Arc::new(b));
    // let mut a2 = a.create();

    // let mut v = vec![1; 10];
    // a.0.read_exact(&mut v);
}
