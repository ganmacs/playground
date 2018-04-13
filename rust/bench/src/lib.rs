#![feature(test)]
extern crate bytes;
extern crate rand;
extern crate test;

mod slice;

pub use bytes::{BufMut, ByteOrder, BytesMut, LittleEndian};
pub use slice::Slice;

const U64_BYTE_SIZE: usize = 8;
const U32_BYTE_SIZE: usize = 4;
const U16_BYTE_SIZE: usize = 2;
const U8_BYTE_SIZE: usize = 1;
pub const COUNT: usize = 2048;

// ========= write 8 =========================================================

pub fn bytes_appned8(v: u8) {
    let mut buf = BytesMut::with_capacity(COUNT);
    for _ in 0..(COUNT) {
        buf.put_u8(v);
    }

    assert!(buf.len() == COUNT)
}

pub fn vector_appned8(v: u8) {
    let mut buf: Vec<u8> = Vec::with_capacity(COUNT);
    for _ in 0..(COUNT) {
        buf.push(v);
    }

    assert!(buf.len() == COUNT)
}

pub fn slice_appned8(v: u8) {
    let mut buf = Slice::with_capacity(COUNT);
    for _ in 0..(COUNT) {
        buf.put_u8(v);
    }

    assert!(buf.len() == COUNT)
}

// ========= write 32=========================================================

pub fn bytes_appned32(v: u32) {
    let mut buf = BytesMut::with_capacity(COUNT * 4);
    for _ in 0..(COUNT) {
        buf.put_u32::<LittleEndian>(v);
    }
    assert!(buf.len() == COUNT * 4)
}

pub fn vector_appned32(v: u32) {
    let mut buf: Vec<u8> = Vec::with_capacity(COUNT * 4);
    for _ in 0..(COUNT) {
        buf.put_u32::<LittleEndian>(v);
    }
    assert!(buf.len() == COUNT * 4)
}

pub fn slice_appned32(v: u32) {
    let mut buf = Slice::with_capacity(COUNT * 4);
    for _ in 0..(COUNT) {
        buf.put_u32(v);
    }
    assert!(buf.len() == COUNT * 4)
}

// get32 =======================================================

pub fn bytes_get32(v: &mut BytesMut) {
    let mut count: usize = 0;
    for i in 0..(COUNT) {
        let ii = i * U32_BYTE_SIZE;
        let k = &v[ii..ii + U32_BYTE_SIZE];
        count += (LittleEndian::read_u32(&k) as usize)
    }
    assert!(COUNT == count);
}

pub fn vector_get32(v: &mut Vec<u8>) {
    let mut count: usize = 0;
    for i in 0..(COUNT) {
        let ii = i * U32_BYTE_SIZE;
        let k = &v[ii..ii + U32_BYTE_SIZE];
        count += (LittleEndian::read_u32(&k) as usize);
    }

    assert!(COUNT == count);
}

pub fn slice_get32(v: &Slice) {
    let mut count: usize = 0;
    for i in 0..(COUNT) {
        let ii = i * U32_BYTE_SIZE;
        let k = &v[ii..ii + U32_BYTE_SIZE];
        count += (LittleEndian::read_u32(&k) as usize)
    }
    assert!(COUNT == count);
}

// create ===================

pub fn bytes_create() {
    for _ in 0..(COUNT) {
        let mut buf = BytesMut::with_capacity(COUNT);
        buf.clone();
    }
}

pub fn vector_create() {
    for _ in 0..(COUNT) {
        let mut buf: Vec<u8> = Vec::with_capacity(COUNT);
        buf.clone();
    }
}

pub fn slice_create() {
    for _ in 0..(COUNT) {
        let mut buf = Slice::with_capacity(COUNT);
        buf.clone();
    }
}

// read =======================

pub fn bytes_read32(v: &mut BytesMut) {
    let mut count: usize = 0;
    for i in 0..(COUNT) {
        let ii = i * U32_BYTE_SIZE;
        let k = &v[ii..ii + U32_BYTE_SIZE];
        count += (LittleEndian::read_u32(&k) as usize)
    }
    assert!(COUNT == count);
}

pub fn vector_read32(v: &mut Vec<u8>) {
    let mut count: usize = 0;
    for i in 0..(COUNT) {
        let ii = i * U32_BYTE_SIZE;
        let k = &v[ii..ii + U32_BYTE_SIZE];
        count += (LittleEndian::read_u32(&k) as usize);
    }

    assert!(COUNT == count);
}

pub fn slice_read32(v: &Slice) {
    let mut count: usize = 0;
    for i in 0..(COUNT) {
        let ii = i * U32_BYTE_SIZE;
        let k = &v[ii..ii + U32_BYTE_SIZE];
        count += (LittleEndian::read_u32(&k) as usize)
    }
    assert!(COUNT == count);
}

pub fn put_u32(b: &mut BytesMut, n: u32) -> usize {
    b.put_u32::<LittleEndian>(n);
    U32_BYTE_SIZE
}

pub fn read_u32(b: &mut BytesMut) -> u32 {
    let v = b.split_to(U32_BYTE_SIZE);
    LittleEndian::read_u32(&v)
}

pub fn seed() -> Vec<u8> {
    let v = [1, 0, 0, 0];
    let mut vv = vec![];

    for i in 0..COUNT {
        vv.extend_from_slice(&v);
    }
    vv
}

#[cfg(test)]
mod tests {

    use rand::Rng;
    use super::*;
    use test::Bencher;

    #[bench]
    fn bench_8_append_bytes(b: &mut Bencher) {
        let v = rand::thread_rng().gen_range(0, 255) as u8;
        b.iter(|| bytes_appned8(v))
    }

    #[bench]
    fn bench_8_append_vector(b: &mut Bencher) {
        let v = rand::thread_rng().gen_range(0, 255) as u8;
        b.iter(|| vector_appned8(v))
    }

    #[bench]
    fn bench_8_append_slice(b: &mut Bencher) {
        let v = rand::thread_rng().gen_range(0, 255) as u8;
        b.iter(|| slice_appned8(v))
    }

    #[bench]
    fn bench_32_append_bytes(b: &mut Bencher) {
        let v = rand::thread_rng().gen_range(0, 255) as u32;
        b.iter(|| bytes_appned32(v))
    }

    #[bench]
    fn bench_32_append_vector(b: &mut Bencher) {
        let v = rand::thread_rng().gen_range(0, 255) as u32;
        b.iter(|| vector_appned32(v))
    }

    #[bench]
    fn bench_32_append_slice(b: &mut Bencher) {
        let v = rand::thread_rng().gen_range(0, 255) as u32;
        b.iter(|| vector_appned32(v))
    }

    #[bench]
    fn bench_32_get_bytes(b: &mut Bencher) {
        let mut v = BytesMut::from(seed());
        b.iter(|| bytes_get32(&mut v))
    }

    #[bench]
    fn bench_32_get_vector(b: &mut Bencher) {
        let mut v = Vec::from(seed());
        b.iter(|| vector_get32(&mut v))
    }

    #[bench]
    fn bench_32_get_slice(b: &mut Bencher) {
        let mut v = Slice::from(&seed());
        b.iter(|| slice_get32(&mut v))
    }

    #[bench]
    fn bench_32_read_bytes(b: &mut Bencher) {
        let mut v = seed();
        b.iter(|| bytes_read32(&mut BytesMut::from(v.clone())))
    }

    #[bench]
    fn bench_32_read_vector(b: &mut Bencher) {
        let mut v = seed();
        b.iter(|| vector_read32(&mut v))
    }

    #[bench]
    fn bench_32_read_slice(b: &mut Bencher) {
        let mut v = seed();
        b.iter(|| slice_read32(&mut Slice::from(&v)))
    }

    #[bench]
    fn bench_create_bytes(b: &mut Bencher) {
        b.iter(|| bytes_create())
    }

    #[bench]
    fn bench_create_vector(b: &mut Bencher) {
        b.iter(|| vector_create())
    }

    #[bench]
    fn bench_create_slice(b: &mut Bencher) {
        b.iter(|| slice_create())
    }
}
