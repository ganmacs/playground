use std::io::{BufWriter, Write};
use std::fs::File;
use bytes::{BufMut, BytesMut, Bytes, LittleEndian};
use crc::{crc32, Hasher32};
use super::{RecordType, HEADER_BYTE_SIZE};

pub struct LogWriter {
    inner: BufWriter<File>,
}

impl LogWriter {
    pub fn new(fd: File) -> LogWriter {
        LogWriter { inner: BufWriter::new(fd) }
    }

    pub fn add_record(&mut self, data: Bytes) {
        self.emit_record(&data, data.len(), RecordType::FULL)
    }

    fn emit_record(&mut self, data: &[u8], length: usize, record_type: RecordType) {
        let mut bytes = BytesMut::with_capacity(HEADER_BYTE_SIZE + length);

        let mut digest = crc32::Digest::new(crc32::IEEE);
        digest.write(data);
        let crc = digest.sum32();
        bytes.put_u32::<LittleEndian>(crc);
        bytes.put_u16::<LittleEndian>(length as u16);
        bytes.put_u8(record_type as u8);
        bytes.put_slice(data);

        self.inner.write(&bytes).unwrap(); // XXX
    }
}
