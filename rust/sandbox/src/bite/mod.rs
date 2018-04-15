use bytes::{BufMut, Bytes};
use bytes::BytesMut;
use std::{cmp, u8};
use byteorder::{ByteOrder, LittleEndian};
use std::io::Read;

pub fn main() {
    // test1();
    // test2();
    // test3();
    // test4();
    test5();
}

pub fn test5() {
    let a = Bytes::from("abcd");

    let mut b = a.clone();
    println!("a={:?}", a);
    println!("b={:?}", b);

    short_successor(b.to_mut());

    println!("a={:?}", a);
    println!("b={:?}", b);
}

pub fn short_successor(val: &mut BytesMut) {
    let l = val.len();

    for i in 0..l {
        let k = val[i];
        if k != u8::MAX {
            val[i] += 1;
            return;
        }
    }
}

pub fn test1() {
    let mut b = BytesMut::from("asldfkjasdfkjasdf");
    let len = b.len();
    for i in 0..len {
        if u8::MAX != b[i] {
            b[i] += 1;
            break;
        }
    }

    println!("{:?}", b);
}

fn test2() {
    let b = Bytes::from(vec![2, 1, 0, 0]);
    let mut c = b.as_ref();
    println!("{:?}", b);
    println!("{:?}", read_u32_i(&mut c));
    println!("{:?}", b);
    println!("{:?}", c);
}

fn test3() {
    let mut b = BytesMut::from(vec![2, 1, 0, 0]);
    println!("{:?}", b);
    // put_u32_i(&mut b, 10);
    // println!("{:?}", b);
}

fn test4() {
    let mut b = BytesMut::from(vec![2, 1, 0, 0]);
    println!("{:?}", b);
    // put_u32_i(&mut b, 10);
    // println!("{:?}", b);
}

pub const U64_BYTE_SIZE: usize = 8;
pub const U32_BYTE_SIZE: usize = 4;
pub const U16_BYTE_SIZE: usize = 2;
pub const U8_BYTE_SIZE: usize = 1;

// pub fn read_u64(b: &mut BytesMut) {
// let buf = self.inner.slice(i, u64_offset);
// let v = LittleEndian::read_u64(&buf) as usize;
// Some(LittleEndian::read_u32(b))
// }

pub fn put_u32_i(b: &mut BytesMut, n: u32) -> usize {
    b.put_u32_le(n);
    U32_BYTE_SIZE
}

pub fn read_u32_i<T: Read>(b: &mut T) -> u32 {
    let mut v = vec![0; U32_BYTE_SIZE];
    b.read(&mut v);
    LittleEndian::read_u32(&v)
}

pub fn get_u32_i<T: Read>(b: &mut T, i: usize) -> u32 {
    let mut v = vec![0; U32_BYTE_SIZE];
    b.read(&mut v);
    LittleEndian::read_u32(&v)
}
