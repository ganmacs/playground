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

const CHECKSUM_SIZE: usize = 4;
const LENGTH_SIZE: usize = 2;
const TYPE_SIZE: usize = 1;
const HEADER_SIZE: usize = CHECKSUM_SIZE + LENGTH_SIZE + TYPE_SIZE;

enum RecordType {
    FULL,
    FIRST,
    MIDDLE,
    LAST,
}

fn crc32(data: &[u8]) -> u32 {
    let mut digest = crc32::Digest::new(crc32::IEEE);
    digest.write(data);
    digest.sum32()
}
