extern crate byteorder;
extern crate bytes;

use byteorder::{ByteOrder, LittleEndian};
use bytes::{BufMut, BytesMut};
use std::collections::HashMap;
use std::{iter, marker, mem, thread, time, io::Write, sync::atomic, sync::{self, mpsc}};

const U16_SIZE: usize = mem::size_of::<u16>();

#[derive(Debug)]
struct Row {
    v: usize,
}

type Rows = Vec<(sync::RwLock<Row>)>;

#[derive(Debug)]
struct Table {
    rows: sync::Arc<sync::RwLock<Rows>>,
}

impl Table {
    pub fn new() -> Self {
        let rows = vec![];
        Self {
            rows: sync::Arc::new(sync::RwLock::new(rows)),
        }
    }

    pub fn insert(&self, val: usize) -> usize {
        let v = sync::RwLock::new(Row { v: val });
        let mut r = self.rows.write().unwrap();
        r.push(v);
        r.len() - 1
    }

    pub fn select_id(&self, id: usize) -> Option<Row> {
        self.rows.read().unwrap().get(id).map(|row| Row {
            v: row.read().unwrap().v,
        })
    }

    pub fn update(&self, id: usize, val: usize) {
        if let Some(v) = self.rows.read().unwrap().get(id) {
            v.write().unwrap().v = val;
        };
    }
}

fn main() {
    let mut threads = vec![];
    let table = sync::Arc::new(Table::new());

    for i in 0..50 {
        let tbl = table.clone();
        let t = thread::Builder::new()
            .name(format!("child {:?}", i))
            .spawn(move || {
                let id = tbl.insert(i);
                // tbl.select_i(1)
            })
            .unwrap();

        threads.push(t);
    }

    for i in 0..50 {
        let tbl = table.clone();
        let t = thread::Builder::new()
            .name(format!("child {:?}", i))
            .spawn(move || {
                tbl.insert(i);
            })
            .unwrap();

        threads.push(t);
    }

    for t in threads {
        if let Err(err) = t.join() {
            println!("{:?}", err);
        }
    }

    let ret = table.rows.read().unwrap();

    println!("size: {:?}", ret.len());

    for item in ret.iter() {
        println!("{:?}", item);
    }
}

// let a = sync::Arc::new(sync::Mutex::new(AsyncVec { inner: Vec::new() }));

// let (tx, rx) = mpsc::channel();
// let (tx_2, rx_2) = mpsc::channel();

// // let b = a.clone();
// let t = thread::Builder::new()
//     .name("sum".to_owned())
//     .spawn(move || loop {
//         let v = rx.recv().unwrap();
//         let mut a = 0;
//         for i in v {
//             a += i;
//         }
//         tx_2.send(a).unwrap();
//     })
//     .unwrap();

// let mut v = vec![];

// for i in 0..100 {
//     v.push(i);
//     if v.len() == 10 {
//         let mut a = Vec::new();
//         std::mem::swap(&mut v, &mut a);
//         tx.send(a).unwrap();
//     }
// }

// let mut a = 0;
// for i in 0..10 {
//     a += rx_2.recv().unwrap()
// }

// println!("{:?}", a);

// t.join().unwrap();

// println!("{:?}", *a.lock().unwrap());
// }

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
