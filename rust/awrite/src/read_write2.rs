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

impl<T: io::Read> Decode<T> {
    pub fn feed(&self, buf: &mut [u8]) -> io::Result<usize> {
        self.inner.lock().unwrap().read(buf)
    }

    pub fn feed_each<'a, F>(&self, buf: &'a mut [u8], f: F) -> io::Result<()>
    where
        F: FnOnce(&'a [u8]) -> (),
    {
        let s = self.inner.lock().unwrap().read(buf);
        Ok(f(buf))
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
    // let decode = Decode::new
    // println!("run");
    // let mut v: Vec<u8> = vec![1, 3, 3, 3, 1, 1];
    // let mut vv: &mut [u8] = v.as_mut();

    // let mut k = "abcd";
    // vv.write(k.as_bytes());
    // println!("{:p}", k);
    // println!("{:p}", vv);
    // println!("{:?}", vv)
    // ;
}
