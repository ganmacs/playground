use std::mem;
use std::fs::File;
use std::io::{BufReader, Read};
use bytes::{BytesMut, Bytes, LittleEndian, ByteOrder};

use super::{HEADER_SIZE, LENGTH_SIZE, TYPE_SIZE, CHECKSUM_SIZE, crc32};

pub struct LogReader {
    inner: BufReader<File>,
}

impl LogReader {
    pub fn new(fd: File) -> Self {
        LogReader { inner: BufReader::new(fd) }
    }

    pub fn read_record(&mut self) -> Result<Bytes, &str> {
        let mut slice = vec![];
        self.inner.read_to_end(&mut slice).unwrap();
        let mut data = Bytes::from(slice);

        if data.len() < HEADER_SIZE {
            // not FULL
            // TODO
            return Err("need more size");
        }

        let mut header = data.split_to(HEADER_SIZE);

        let expected_checksum = {
            let c = header.split_to(CHECKSUM_SIZE);
            LittleEndian::read_u32(&c)
        };

        let length = {
            let c = header.split_to(LENGTH_SIZE);
            LittleEndian::read_u16(&c)
        };

        let rtype = {
            let c = header.split_to(TYPE_SIZE);
            c[0]
        };

        // XXX must check whether record is full or not
        let record = data.split_to(length as usize);

        if crc32(&record) != expected_checksum {
            println!("invalid");
            return Err("validation failed");
        }

        Ok(record)
    }
}
