use byteorder::{LittleEndian, ByteOrder};
use bytes::{BufMut, BytesMut, Bytes};

const COUNT_INDEX: usize = 8;
const RECORD_INDEX: usize = 12;

const BLOCK_SIZE: usize = 1024 * 4; // 4K
const SEQ_SIZE: usize = 8;
const COUNT_SIZE: usize = 4;

enum KeyKind {
    SET,
    DELETE,
}

// Need External Lock
pub struct WriteBatch {
    // data: | seq (8byte) | count (4byte) | record (n byte) |
    // record: | type value (1 byte) | key len (4bytes) | key | value len (4bytes) | value |
    data: BytesMut,
}

impl WriteBatch {
    pub fn new() -> Self {
        let mut data = BytesMut::with_capacity(BLOCK_SIZE);
        data.put_u64::<LittleEndian>(0); // seq
        data.put_u32::<LittleEndian>(0); // count
        WriteBatch { data }
    }

    pub fn load_data(mut data: Bytes) -> Self {
        let wb = Self::new();
        let seq = {
            let c = data.split_off(SEQ_SIZE);
            LittleEndian::read_u64(c.as_ref())
        };

        println!("{:?}", seq);

        let count = {
            let c = data.split_off(COUNT_SIZE);
            LittleEndian::read_u32(c.as_ref())
        };

        println!("{:?}", count);

        for _ in 0..count {
            let t = {
                let c = data.split_off(1);
                LittleEndian::read_u32(c.as_ref())
            };

            println!("{:?}", t);
        }

        wb
    }

    pub fn data(self) -> Bytes {
        self.data.freeze()
    }

    pub fn put(&mut self, key: &str, value: &str) {
        self.inc_count();
        self.data.put_u8(KeyKind::SET as u8);
        self.append_str(key);
        self.append_str(value);
    }

    fn append_str(&mut self, value: &str) {
        // TODO: use varint
        let value_size = value.len();
        self.data.put_u32::<LittleEndian>(value_size as u32);
        self.data.put_slice(value.as_bytes());
    }

    fn inc_count(&mut self) {
        let c = *self.data.get(COUNT_INDEX).unwrap();
        let size = self.data.len();
        self.data.swap(c as usize, size - 1);
        self.data.truncate(size);
    }
}
