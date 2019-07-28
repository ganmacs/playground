use std::cell::RefCell;
use std::io;
use std::io::Read as _;
use std::io::Write as _;
use std::sync;

#[derive(Debug)]
struct MLock<T> {
    arc: sync::Arc<sync::Mutex<T>>,
}

impl<T> Clone for MLock<T> {
    fn clone(&self) -> Self {
        MLock {
            arc: self.arc.clone(),
        }
    }
}

impl<T> MLock<T> {
    pub fn new(val: T) -> Self {
        MLock {
            arc: sync::Arc::new(sync::Mutex::new(val)),
        }
    }

    pub fn lock(&self) -> Result<sync::MutexGuard<T>, ()> {
        // is it ok that it will ingore an error
        (*self.arc).lock().map_err(|e| {})
    }
}

pub trait BufferedRead<'a>: io::Read {
    fn fill_buf(&self) -> io::Result<&'a [u8]>;

    fn consume(&mut self, len: usize);
}

impl<'a> BufferedRead<'a> for &'a [u8] {
    fn fill_buf(&self) -> io::Result<&'a [u8]> {
        Ok(self)
    }

    fn consume(&mut self, len: usize) {
        *self = &(*self)[len..];
    }
}

impl<'a> BufferedRead<'a> for io::Cursor<&'a [u8]> {
    fn fill_buf(&self) -> io::Result<&'a [u8]> {
        let len = std::cmp::min(self.position(), self.get_ref().len() as u64);
        Ok(&self.get_ref()[len as usize..])
    }

    fn consume(&mut self, len: usize) {
        let pos = self.position();
        self.set_position(pos + len as u64);
    }
}

struct Decode<T> {
    inner: MLock<T>,
    // bytes:
}

impl<T> Decode<T> {
    pub fn new(val: T) -> Self {
        Decode {
            inner: MLock::new(val),
        }
    }
}

impl<T: io::Write> Decode<T> {
    pub fn feed(&self, buf: &[u8]) -> io::Result<usize> {
        self.inner.lock().unwrap().write(buf)
    }

    pub fn feed_each<'a, F>(&self, buf: &'a [u8], f: F) -> io::Result<()>
    where
        F: Fn(&'a u8) -> (),
    {
        let s = self.inner.lock().unwrap().write(buf);
        for item in buf {
            f(item)
        }
        Ok(())
    }
}

impl<T: io::Write> io::Write for Decode<T> {
    fn write(&mut self, buf: &[u8]) -> io::Result<usize> {
        self.inner.lock().unwrap().write(buf)
    }

    fn flush(&mut self) -> io::Result<()> {
        self.inner.lock().unwrap().flush()
    }
}

impl<T: io::Read> io::Read for Decode<T> {
    fn read(&mut self, buf: &mut [u8]) -> io::Result<usize> {
        self.inner.lock().unwrap().read(buf)
    }
}

impl<'a, R: BufferedRead<'a>> BufferedRead<'a> for Decode<R> {
    fn fill_buf(&self) -> io::Result<&'a [u8]> {
        self.inner.lock().unwrap().fill_buf()
    }

    fn consume(&mut self, len: usize) {
        self.inner.lock().unwrap().consume(len)
    }
}

pub fn run() {
    // let mut v: Vec<u8> = vec![];
    // let c = io::Cursor::new(v.as_mut_slice());
    // let d = Decode::new(c);
    // let body = "asdfghjkl";
    // d.feed_each(body.as_bytes(), |v| println!("{:?}", v))
    // .unwrap();

    // let decode = Decode::new
    // println!("run");
    let mut v: Vec<u8> = vec![1; 10];
    // let mut vv: &mut [u8] = v.as_mut();
    let mut v = io::Cursor::new(v);
    v.write(b"test");
    println!("{:?}", v);
    let mut buf = vec![0; 10];
    v.read(&mut buf);
    println!("{:?}", buf);
    println!("{:?}", v);

    // let mut k = "abcd";
    // vv.write(k.as_bytes());
    // println!("{:p}", k);
    // println!("{:p}", vv);
    // println!("{:?}", vv)
    // ;
}
