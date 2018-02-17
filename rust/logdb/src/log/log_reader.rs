use std::mem;
use std::fs::File;
use std::io::{BufReader, Read};

use super::HEADER_BYTE_SIZE;

pub struct LogReader {
    inner: BufReader<File>,
}

impl LogReader {
    pub fn new(fd: File) -> Self {
        LogReader { inner: BufReader::new(fd) }
    }

    pub fn read_record(&mut self) {
        // let mut buf = vec![];
        let mut b: [u8; HEADER_BYTE_SIZE] = unsafe { mem::uninitialized() };
        self.inner.read_exact(&mut b);
        println!("{:?}", b);
        // println!("{:?}", buf);
        // read_to_end(&mut buf).unwrap();
    }
}
