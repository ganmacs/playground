use bytes::{BufMut, BytesMut, Bytes, LittleEndian, ByteOrder};
// use memdb::MemDB;
use std::iter::{Iterator, IntoIterator};

const COUNT_INDEX: usize = 8;
const RECORD_INDEX: usize = 12;

const BLOCK_SIZE: usize = 1024 * 4; // 4K
const SEQ_SIZE: usize = 8;
const COUNT_SIZE: usize = 4;
const TYPE_SIZE: usize = 1;
const KEY_LENGTH_SIZE: usize = 4;
const VALUE_LENGTH_SIZE: usize = 4;

#[derive(Debug)]
pub enum KeyKind {
    SET,
    DELETE,
}

type Key = Bytes;
type Value = Bytes;

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

    pub fn count(&self) -> usize {
        self.count as usize
    }
}

impl IntoIterator for WriteBatch {
    type Item = (KeyKind, Bytes, Bytes);
    type IntoIter = WriteBatchIterator;

    fn into_iter(self) -> Self::IntoIter {
        WriteBatchIterator {
            data: self.data.freeze(),
            count: self.count as usize,
            idx: 0,
            pos: 0,
        }
    }
}

impl Iterator for WriteBatchIterator {
    type Item = (KeyKind, Key, Value);

    fn next(&mut self) -> Option<Self::Item> {
        if self.is_eob() {
            return None;
        }

        let typev = {
            let d = self.data.slice(self.pos, self.pos + TYPE_SIZE);
            self.pos += TYPE_SIZE;
            if d[0] == 0 {
                KeyKind::SET
            } else {
                KeyKind::DELETE
            }
        };

        let key = {
            let key_len = {
                let d = self.data.slice(self.pos, self.pos + KEY_LENGTH_SIZE);
                self.pos += KEY_LENGTH_SIZE;
                LittleEndian::read_u32(&d) as usize
            };

            let key = self.data.slice(self.pos, self.pos + key_len);
            self.pos += key_len;
            key
        };

        let value = {
            let value_len = {
                let d = self.data.slice(self.pos, self.pos + VALUE_LENGTH_SIZE);
                self.pos += KEY_LENGTH_SIZE;
                LittleEndian::read_u32(&d) as usize
            };

            let value = self.data.slice(self.pos, self.pos + value_len);
            self.pos += value_len;
            value
        };

        self.idx += 1;
        Some((typev, key, value))
    }
}

pub struct WriteBatchIterator {
    data: Bytes,
    idx: usize,
    count: usize,
    pos: usize,
}

impl WriteBatchIterator {
    fn is_eob(&self) -> bool {
        self.idx >= self.count
    }
}
