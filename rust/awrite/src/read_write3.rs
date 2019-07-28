use bytes;
use std::cmp;
use std::io;
use std::ptr;

use bytes::Buf;
use bytes::BufMut;
use std::io::{Read, Write};

#[derive(Debug)]
struct A<B> {
    buf: B,
}

// struct B<'a> {
//     buf: &'a [u8],
// }

// no need read !!
pub trait BufferedRead<'a>: io::Read {
    fn fill_buf(&self) -> io::Result<&'a [u8]>;

    fn consume(&mut self, len: usize);
}

trait C {
    fn test<'a>(&'a self) -> &'a [u8];
}

impl<'a, B> BufferedRead<'a> for A<&'a mut B>
where
    B: Buf + AsRef<&'a [u8]>,
{
    fn fill_buf(&self) -> io::Result<&'a [u8]> {
        Ok(*self.as_ref())
    }

    fn consume(&mut self, len: usize) {
        self.buf.advance(len)
    }
}

impl<B> io::Read for A<B>
where
    B: Buf,
{
    fn read(&mut self, buf: &mut [u8]) -> io::Result<usize> {
        let len = cmp::min(self.buf.remaining(), buf.len());

        Buf::copy_to_slice(&mut self.buf, &mut buf[0..len]);
        Ok(len)
    }
}

impl<B> io::Write for A<B>
where
    B: BufMut,
{
    fn write(&mut self, buf: &[u8]) -> io::Result<usize> {
        let n = cmp::min(self.buf.remaining_mut(), buf.len());

        self.buf.put(&buf[0..n]);
        Ok(n)
    }

    fn flush(&mut self) -> io::Result<()> {
        Ok(())
    }
}

impl<'a, B> AsRef<&'a [u8]> for A<&'a mut B>
where
    B: AsRef<&'a [u8]>,
{
    #[inline]
    fn as_ref(&self) -> &&'a [u8] {
        &*self.buf.as_ref()
    }
}

// impl<'a> AsRef<&'a [u8]> for io::Cursor<&'a [u8]> {
//     #[inline]

//     fn as_ref(&self) -> &&'a [u8] {
//         self.get_ref()
//     }
// }

pub fn run() {
    let mut a = A {
        buf: bytes::BytesMut::new(),
    };

    // a.fill_buf()

    // let text = "test";

    // a.write(text.as_bytes());

    // let mut buf: Vec<u8> = vec![0; 4];
    // let r = a.read(buf.as_mut()).unwrap();
    // println!("buf={:?} r={:?} a={:?}", buf, r, a);

    // let r = a.read(buf.as_mut()).unwrap();
    // // let r = a.read(buf.as_mut()).unwrap();

    // println!("buf={:?} r={:?} a={:?}", buf, r, a);

    // a.write(text.as_bytes());

    // println!("buf={:?} r={:?} a={:?}", buf, r, a);
}
