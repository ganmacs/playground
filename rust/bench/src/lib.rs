#![feature(test)]
extern crate rand;
extern crate test;
extern crate bytes;

use bytes::{BufMut, BytesMut};

pub fn bytes_appned(v: u8) {
    let mut buf = BytesMut::with_capacity(10 * 1024);
    for _ in 0..(10 * 1024) {
        buf.put_u8(v);
    }

    let mut vv = true;
    let ret = Some(&v);
    for i in 0..(10 * 1024) {
        if buf.get(i) != ret {
            vv = false
        }
    }
    assert!(vv)
}

pub fn vector_appned(v: u8) {
    let mut buf: Vec<u8> = Vec::with_capacity(10 * 1024);
    for _ in 0..(10 * 1024) {
        buf.push(v);
    }

    let mut vv = true;
    let ret = Some(&v);
    for i in 0..(10 * 1024) {
        if buf.get(i) != ret {
            vv = false
        }
    }
    assert!(vv)
}

pub fn array_appned(v: u8) {
    let mut buf: [u8; 1024 * 5] = [0; 1024 * 5];
    for i in 0..(4 * 1024) {
        buf[i] = v;
    }

    let mut vv = true;
    for i in 0..(4 * 1024) {
        if buf[i] == v {
            vv = false
        }
    }
}

#[cfg(test)]
mod tests {

    use rand::Rng;
    use super::*;
    use test::Bencher;

    #[test]
    fn tset_run() {
        bytes_appned(10)
    }

    #[bench]
    fn bench_bytes_append(b: &mut Bencher) {
        let v = rand::thread_rng().gen_range(0, 255) as u8;
        b.iter(|| bytes_appned(v))
    }

    #[bench]
    fn bench_vector_append(b: &mut Bencher) {
        let v = rand::thread_rng().gen_range(0, 255) as u8;
        b.iter(|| vector_appned(v))
    }

    #[bench]
    fn bench_array_append(b: &mut Bencher) {
        let v = rand::thread_rng().gen_range(0, 255) as u8;
        b.iter(|| array_appned(v))
    }
}
