use memmap::*;
use std::io::{BufReader, Cursor, Read, Seek, SeekFrom, Write};
use std::fs::File;
use std::sync::Arc;
use std::cell::RefCell;

pub fn main() {
    // test1();
    // test2();
    // test3();
    test4();
    // test5();
}

struct C(Arc<Mmap>);

impl C {
    pub fn create(&self) -> C {
        C(self.0.clone())
    }

    pub fn read_at(&self, offset: usize, size: usize) {
        let v = &self.0[offset..offset + size];
        println!("{:?}", v);
    }
}

fn test4() {
    let file = File::open("Cargo.toml").unwrap();
    let f = unsafe { MmapOptions::new().map(&file).unwrap() };
    let k = C(Arc::new(f));

    k.read_at(10, 20);
    k.read_at(11, 12);
    k.read_at(13, 30);

    let v = k.create();
    v.read_at(20, 300);
}

struct B(Arc<RefCell<BufReader<Cursor<Vec<u8>>>>>);

impl B {
    pub fn create(&self) -> B {
        B(self.0.clone())
    }

    pub fn write(&self, i: usize) {
        let mut r = self.0.borrow_mut();
        let k = r.get_mut().get_mut();
        k[i] = 10;
    }

    pub fn print(&self) {
        println!("{:?}", self.0);
    }

    pub fn read_at(&self, offset: usize, size: usize) {
        let mut v = vec![0; size];
        let mut reader = self.0.borrow_mut();
        reader.seek(SeekFrom::Start(offset as u64)).unwrap();
        reader.read(&mut v);

        println!("{:?}", v);
    }
}

fn test3() {
    let buff: Cursor<Vec<u8>> = Cursor::new((1..15).collect());
    let b = BufReader::new(buff);
    let b = B(Arc::new(RefCell::new(b)));

    {
        b.write(12);
        b.read_at(10, 4);
        b.print()
    }

    {
        let b2 = b.create();
        b2.write(11);
        b.read_at(10, 4);
        b2.print()
    }
}

fn test2() {
    let buff = Cursor::new(vec![1; 15]);
    let b = BufReader::new(buff);

    let b = B(Arc::new(RefCell::new(b)));

    {
        b.write(1);
        b.print()
    }

    {
        let b2 = b.create();
        b2.write(2);
        b2.print()
    }
}

struct A(Arc<BufReader<Cursor<Vec<u8>>>>);

impl A {
    pub fn create(&self) -> A {
        A(self.0.clone())
    }

    pub fn get_mut(&mut self) -> &mut BufReader<Cursor<Vec<u8>>> {
        Arc::get_mut(&mut self.0).unwrap()
    }
}

fn test1() {
    let buff = Cursor::new(vec![1; 15]);
    let mut b = BufReader::new(buff);

    {
        let k = b.get_mut().get_mut();
        k[2] = 10;
        println!("{:?}", k);
    }

    let mut a = A(Arc::new(b));
    {
        let v1 = a.get_mut();
        let v = v1.get_mut().get_mut();
        v[1] = 10;
        println!("{:?}", v);
    }

    {
        let mut b = a.create();
        let v1 = b.get_mut(); // error occurred
        let v = v1.get_mut().get_mut();
        v[3] = 10;
        println!("{:?}", v);
    }
}
