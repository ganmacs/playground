use std::io::Write;
use bytes::{BufMut, BytesMut, Bytes, LittleEndian};
use super::{RecordType, HEADER_SIZE, BLOCK_SIZE, crc32};

pub struct LogWriter<T: Write> {
    inner: T,
    offset: usize,
}

impl<T: Write> LogWriter<T> {
    pub fn new(writer: T) -> LogWriter<T> {
        LogWriter {
            inner: writer,
            offset: 0,
        }
    }

    pub fn add_record(&mut self, data: Bytes) {
        let mut left = data.len();
        let mut begin = true;

        while left > 0 {
            let leftover = BLOCK_SIZE - self.offset;
            if leftover < HEADER_SIZE {
                if leftover > 0 {
                    let trailer: Vec<u8> = vec![0; leftover];
                    self.inner.write(trailer.as_ref()).unwrap();
                }
                self.offset = 0;
            }

            let available = BLOCK_SIZE - self.offset - HEADER_SIZE;
            let fragment_size = if available > left { left } else { available };
            let end = left == fragment_size;

            let kind = if begin && end {
                RecordType::FULL
            } else if begin {
                RecordType::FIRST
            } else if end {
                RecordType::LAST
            } else {
                RecordType::MIDDLE
            };

            // println!(
            //     "fragment_size: {:?}, available: {:?}, end: {:?}, left: {:?}",
            //     fragment_size,
            //     available,
            //     end,
            //     left,
            // );

            let data = data.slice(self.offset, self.offset + fragment_size);
            self.emit_record(&data, fragment_size, kind);
            left -= fragment_size;
            begin = false;
        }
    }

    fn emit_record(&mut self, data: &Bytes, length: usize, record_type: RecordType) {
        let mut bytes = BytesMut::with_capacity(HEADER_SIZE + length);

        let crc = crc32(data);
        bytes.put_u32::<LittleEndian>(crc);
        bytes.put_u16::<LittleEndian>(length as u16);
        bytes.put_u8(record_type as u8);
        bytes.extend(data);
        let s = self.inner.write(&bytes).unwrap();
        self.offset += s;
    }
}


#[cfg(test)]
mod tests {
    use super::{LogWriter, RecordType, BLOCK_SIZE};
    use bytes::{Bytes, ByteOrder, LittleEndian};

    fn crc_bytes(offset: &mut usize) {
        *offset += 4
    }

    fn length_bytes(b: &Bytes, offset: &mut usize) -> usize {
        let c = b.slice(*offset, *offset + 2);
        *offset += 2;
        LittleEndian::read_u16(&c) as usize
    }

    fn type_bytes(b: &Bytes, offset: &mut usize) -> usize {
        let c = b.slice(*offset, *offset + 1);
        *offset += 1;
        c[0] as usize
    }

    #[test]
    fn write_full_record() {
        let mut lw = LogWriter::new(Vec::new());
        let b = Bytes::from("key");
        let size = b.len();
        lw.add_record(b);
        let data = Bytes::from(lw.inner);

        let mut offset = 0;
        crc_bytes(&mut offset);

        let length = length_bytes(&data, &mut offset);
        assert_eq!(length, size);

        let rec_type = type_bytes(&data, &mut offset);
        assert_eq!(rec_type, RecordType::FULL as usize);
    }

    #[test]
    fn write_big_data_to_record() {
        let mut lw = LogWriter::new(Vec::new());
        let b = {
            // across BLOCK_SIZE
            let mut byte = Bytes::with_capacity(BLOCK_SIZE + 300);
            for _ in 0..(BLOCK_SIZE / 15) {
                byte.extend(b"1234567890123456789012345678901")
            }
            byte
        };
        let size = b.len();
        lw.add_record(b);
        let data = Bytes::from(lw.inner);
        let full_data_size = BLOCK_SIZE - 7; // 7 is header size

        let mut offset = 0;
        crc_bytes(&mut offset);
        let length = length_bytes(&data, &mut offset);
        assert_eq!(length, full_data_size);
        let rec_type = type_bytes(&data, &mut offset);
        assert_eq!(rec_type, RecordType::FIRST as usize);
        offset += full_data_size;

        crc_bytes(&mut offset);
        let length = length_bytes(&data, &mut offset);
        assert_eq!(length, full_data_size);
        let rec_type = type_bytes(&data, &mut offset);
        assert_eq!(rec_type, RecordType::MIDDLE as usize);
        offset += full_data_size;

        crc_bytes(&mut offset);
        let length = length_bytes(&data, &mut offset);
        assert_eq!(length, size - (2 * full_data_size));
        let rec_type = type_bytes(&data, &mut offset);
        assert_eq!(rec_type, RecordType::LAST as usize);
    }
}
