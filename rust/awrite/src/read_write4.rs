use bytes;
use std::cmp;
use std::io;
use std::ptr;

use bytes::Buf;
use bytes::BufMut;
use std::io::{Cursor, Read, Write};

use std::sync;

type MLock<T> = sync::Arc<sync::Mutex<T>>;

struct A {
    c: Cursor<bytes::Bytes>,
}

pub fn run() {
    let c = Cursor::new(bytes::Bytes::new());

    // let v = c.write(b"lakjsdf;ljalksjdf;lak");
    let k = "aaaaa";
    // let v = c.write(k.as_bytes());
}
