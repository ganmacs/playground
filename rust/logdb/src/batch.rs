use bytes::{BufMut, BytesMut, Bytes, LittleEndian, ByteOrder};
use memdb::MemDB;

const COUNT_INDEX: usize = 8;
const RECORD_INDEX: usize = 12;

const BLOCK_SIZE: usize = 1024 * 4; // 4K
const SEQ_SIZE: usize = 8;
const COUNT_SIZE: usize = 4;
const TYPE_SIZE: usize = 1;
const KEY_LENGTH_SIZE: usize = 4;
const VALUE_LENGTH_SIZE: usize = 4;

pub enum KeyKind {
    SET,
    DELETE,
}

// Need External Lock
// data: | seq (8byte) | count (4byte) | record (n byte) |
// record: | type value (1 byte) | key len (4bytes) | key | value len (4bytes) | value |
pub struct WriteBatch {
    seq: u64,
    count: u32,
    data: BytesMut,
}

impl WriteBatch {
    pub fn new() -> Self {
        WriteBatch {
            seq: 0,
            count: 0,
            data: BytesMut::with_capacity(BLOCK_SIZE),
        }
    }

    pub fn load_data(mut data: Bytes) -> Self {
        let seq = {
            let c = data.split_to(SEQ_SIZE);
            LittleEndian::read_u64(c.as_ref())
        };

        let count = {
            let c = data.split_to(COUNT_SIZE);
            LittleEndian::read_u32(c.as_ref())
        };

        let data = data.try_mut().unwrap();
        WriteBatch { seq, count, data }
    }

    pub fn insert_memory(self, mem: &mut MemDB) {
        let mut data = self.data.freeze();

        for _ in 0..self.count {
            let typev = {
                let d = data.split_to(TYPE_SIZE);
                d[0]
            };

            let key = {
                let key_len = {
                    let d = data.split_to(KEY_LENGTH_SIZE);
                    LittleEndian::read_u32(&d) as usize
                };

                let d = data.split_to(key_len);
                Vec::from(&d as &[u8])
            };

            let value = {
                let value_len = {
                    let d = data.split_to(VALUE_LENGTH_SIZE);
                    LittleEndian::read_u32(&d) as usize
                };

                let d = data.split_to(value_len);
                Vec::from(&d as &[u8])
            };

            mem.insert(key, value);
        }
    }

    pub fn data(&self) -> Bytes {
        let mut v = BytesMut::with_capacity(RECORD_INDEX);
        v.put_u64::<LittleEndian>(self.seq);
        v.put_u32::<LittleEndian>(self.count);
        v.extend(self.data.clone()); // XXX
        v.freeze()
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
        self.count += 1;
    }
}
