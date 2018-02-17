use std::io::{BufWriter, Write};
use std::fs::File;
use bytes::{BufMut, BytesMut, Bytes, LittleEndian};
use super::{RecordType, HEADER_SIZE, crc32};

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
        let mut bytes = BytesMut::with_capacity(HEADER_SIZE + length);

        let crc = crc32(data);
        bytes.put_u32::<LittleEndian>(crc);
        bytes.put_u16::<LittleEndian>(length as u16);
        bytes.put_u8(record_type as u8);
        bytes.put_slice(data);

        self.inner.write(&bytes).unwrap(); // XXX
    }
}
