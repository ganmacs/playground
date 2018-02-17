mod log_writer;
mod log_reader;

pub use self::log_reader::LogReader;
pub use self::log_writer::LogWriter;

// block := record* trailer?
// record :=
//   checksum: uint32     // crc32c of type and data[] ; little-endian
//   length: uint16       // little-endian
//   type: uint8          // One of FULL, FIRST, MIDDLE, LAST
//   data: uint8[length]


const HEADER_BYTE_SIZE: usize = 12;

enum RecordType {
    FULL,
    FIRST,
    MIDDLE,
    LAST,
}
