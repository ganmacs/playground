use std::io::Read;
use bytes::{Bytes, LittleEndian, ByteOrder, BytesMut};
use super::{RecordType, BLOCK_SIZE, HEADER_SIZE, LENGTH_SIZE, TYPE_SIZE, CHECKSUM_SIZE, crc32};

pub struct LogReader<T: Read> {
    inner: T,
}

impl<T: Read> LogReader<T> {
    pub fn new(reader: T) -> Self {
        LogReader { inner: reader }
    }

    pub fn read_record(&mut self) -> Result<Bytes, &str> {
        let mut slice = Bytes::with_capacity(BLOCK_SIZE);
        let record_type = self.read_physical_record(&mut slice);

        // TODO fragment
        match record_type {
            Ok(RecordType::FULL) => (),
            Ok(RecordType::FIRST) => {
                slice.extend(self.read_record().unwrap());

            }
            Ok(RecordType::MIDDLE) => {
                slice.extend(self.read_record().unwrap());
            }
            Ok(RecordType::LAST) => (),
            Ok(RecordType::EOF) => (),
            Err(e) => panic!(e),
        }

        Ok(slice)
    }

    fn read_physical_record(&mut self, ret: &mut Bytes) -> Result<RecordType, &'static str> {
        let mut v = [0; BLOCK_SIZE];
        let s = self.inner.read(&mut v).unwrap();
        if s == 0 {
            return Ok(RecordType::EOF);
        }
        let mut slice = BytesMut::from(&v as &[u8]); // ignore size

        if slice.len() < HEADER_SIZE {
            return Err("need more size");
        }

        let mut header = slice.split_to(HEADER_SIZE);

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
            RecordType::from(c[0])
        };

        let record = slice.split_to(length as usize);
        if crc32(&record) != expected_checksum {
            println!("invalid");
            return Err("validation failed");
        }
        ret.extend(record);
        Ok(rtype)
    }
}

// #[cfg(test)]
// mod tests {
//     use batch::WriteBatch;
//     use std::fs;
//     use std::io::BufReader;
//     use super::LogReader;

//     #[test]
//     fn read_full_record() {
//         let reader = BufReader::new(fs::File::open("test/data/full_record.log").unwrap());
//         let mut lr = LogReader::new(reader);
//         let s = lr.read_record().unwrap();
//         let batch = WriteBatch::load_data(s);
//         assert_eq!(batch.count(), 1);
//     }

//     #[test]
//     fn read_across_record() {
//         let reader = BufReader::new(fs::File::open("test/data/across_record.log").unwrap());
//         let mut lr = LogReader::new(reader);
//         let s = lr.read_record().unwrap();
//         let batch = WriteBatch::load_data(s);
//         assert_eq!(batch.count(), 1);
//     }
// }
