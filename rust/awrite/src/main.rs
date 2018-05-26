extern crate byteorder;
extern crate bytes;

use byteorder::{ByteOrder, LittleEndian};
use bytes::{BufMut, BytesMut};
use std::{mem, sync, thread, io::Write};

const U16_SIZE: usize = mem::size_of::<u16>();

fn main() {
    let a = sync::Arc::new(sync::Mutex::new(Vec::new()));

    let b = a.clone();
    let t = thread::Builder::new()
        .name("sum".to_owned())
        .spawn(move || loop {
            let mut k = b.lock().unwrap();
            if k.len() >= 2 {
                let a = k.pop().unwrap();
                let b = k.pop().unwrap();
                let c = a + b;
                k.push(c);

                println!("{:?}", *k);
                if c == 4950 {
                    break;
                }
            }
        })
        .unwrap();

    for i in 0..100 {
        let mut k = a.lock().unwrap();
        k.push(i);
    }

    t.join().unwrap();

    println!("{:?}", *a.lock().unwrap());
}

struct AsyncWriter<T> {
    buffer: BytesMut,
    writer: T,
    size: u64,
}

impl<T> AsyncWriter<T> {
    pub fn new(w: T) -> Self {
        Self {
            writer: w,
            buffer: BytesMut::new(),
            size: 0,
        }
    }

    pub fn start(&self) {}
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
