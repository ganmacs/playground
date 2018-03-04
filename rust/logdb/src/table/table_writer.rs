use std::io::Write;
use bytes::Bytes;

pub struct TableWriter<T: Write> {
    inner: T,
    offset: usize,
}

impl<T: Write> TableWriter<T> {
    pub fn new(writer: T) -> TableWriter<T> {
        TableWriter {
            inner: writer,
            offset: 0,
        }
    }

    pub fn add(&mut self, key: &Bytes, value: &Bytes) {
        self.offset += key.len() + value.len();
        println!("{:?}=>{:?}", key, value);
    }

    pub fn size(&self) -> usize {
        self.offset
    }
}
