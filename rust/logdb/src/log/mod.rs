mod log_writer;
mod log_reader;

use crc::{crc32, Hasher32};
pub use self::log_reader::LogReader;
pub use self::log_writer::LogWriter;

// block := record* trailer?
// record :=
//   checksum: uint32     // crc32c of type and data[] ; little-endian
//   length: uint16       // little-endian
//   type: uint8          // One of FULL, FIRST, MIDDLE, LAST
//   data: uint8[length]

const BLOCK_SIZE: usize = 2 << 15; // original leveldb defined
const CHECKSUM_SIZE: usize = 4;
const LENGTH_SIZE: usize = 2;
const TYPE_SIZE: usize = 1;
const HEADER_SIZE: usize = CHECKSUM_SIZE + LENGTH_SIZE + TYPE_SIZE;

#[derive(Debug)]
enum RecordType {
    FULL,
    FIRST,
    MIDDLE,
    LAST,
    EOF,
}

impl RecordType {
    fn from(v: u8) -> Self {
        match v {
            0 => RecordType::FULL,
            1 => RecordType::FIRST,
            2 => RecordType::MIDDLE,
            3 => RecordType::LAST,
            4 => RecordType::EOF,
            _ => unreachable!(),
        }
    }
}

fn crc32(data: &[u8]) -> u32 {
    let mut digest = crc32::Digest::new(crc32::IEEE);
    digest.write(data);
    digest.sum32()
}
