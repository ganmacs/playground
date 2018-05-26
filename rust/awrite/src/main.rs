extern crate byteorder;
extern crate bytes;

use byteorder::{ByteOrder, LittleEndian};
use bytes::{BufMut, BytesMut};
use std::{mem, thread, io::Write, sync::{self, mpsc}};

const U16_SIZE: usize = mem::size_of::<u16>();

struct AsyncVec<T> {
    inner: Vec<T>,
}

fn main() {
    // let a = sync::Arc::new(sync::Mutex::new(AsyncVec { inner: Vec::new() }));

    let (tx, rx) = mpsc::channel();
    let (tx_2, rx_2) = mpsc::channel();

    // let b = a.clone();
    let t = thread::Builder::new()
        .name("sum".to_owned())
        .spawn(move || loop {
            let v = rx.recv().unwrap();
            let mut a = 0;
            for i in v {
                a += i;
            }
            tx_2.send(a).unwrap();
        })
        .unwrap();

    let mut v = vec![];

    for i in 0..100 {
        v.push(i);
        if v.len() == 10 {
            let mut a = Vec::new();
            std::mem::swap(&mut v, &mut a);
            tx.send(a).unwrap();
        }
    }

    let mut a = 0;
    for i in 0..10 {
        a += rx_2.recv().unwrap()
    }

    println!("{:?}", a);

    // t.join().unwrap();

    // println!("{:?}", *a.lock().unwrap());
}

impl<T> AsyncVec<T> {
    pub fn new() -> Self {
        Self { inner: Vec::new() }
    }

    // pub fn start(&mut self) {
    // let (tx_1, rx_1) = mpsc::channel();
    // let (tx_2, rx_2) = mpsc::channel();
    // }

    pub fn len(&self) -> usize {
        self.len()
    }

    pub fn push(&self, v: T) {
        self.push(v);
    }

    pub fn pop(&self) -> Option<T> {
        self.pop()
    }
}

struct AsyncWriter<T> {
    buffer: BytesMut,
    writer: Option<T>,
    size: u64,
}

impl<T> AsyncWriter<T> {
    const BUFFER_SIZE: usize = 1024;

    pub fn new(w: T) -> Self {
        Self {
            writer: Some(w),
            buffer: BytesMut::new(),
            size: 0,
        }
    }

    // pub fn start(&self) {
    //     let a = sync::Arc::new(sync::Mutex::new(Vec::new()));
    //     thread::Builder::new()
    //         .name("async writer".to_string())
    //         .spawn(move || loop {})
    // }

    // pub fn value(&self) {}
}

impl<T: Write> AsyncWriter<T> {
    pub fn add(&mut self, v: &str) {
        self.size += self.write_with_u32_prefix(v) as u64;
    }

    fn write_with_u32_prefix(&mut self, v: &str) -> usize {
        self.buffer.put_u16_le(v.len() as u16);
        self.buffer.put(v);
        v.len() + U16_SIZE
    }
}
