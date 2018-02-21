mod node_arena;
mod node;
mod fixed_list;
mod skiplist;

use ikey::InternalKey;
use bytes::{Bytes, LittleEndian, ByteOrder};
use batch::KeyKind;

const MAX_HEIGHT: usize = 12;

pub struct MemDB {
    inner: skiplist::SkipList,
}

impl MemDB {
    pub fn new() -> Self {
        MemDB { inner: skiplist::SkipList::new() }
    }

    // Should be LookupKey
    pub fn get(&self, key: &InternalKey) -> Option<String> {
        let v = key.memtable_key();
        self.inner.get(&Vec::from(&v as &[u8]))
    }

    pub fn add(&mut self, key_kind: KeyKind, ukey: Bytes, value: Bytes) -> bool {
        let n = ukey.len();
        let mut buf = [0; 4];
        LittleEndian::write_u32(&mut buf, n as u32);
        let mut key = Bytes::from(buf.to_vec());
        key.extend(ukey);

        match key_kind {
            KeyKind::SET => {
                self.inner.insert(
                    Vec::from(&key as &[u8]),
                    Vec::from(&value as &[u8]),
                )
            }
            KeyKind::DELETE => false,    // TODO
        }
    }
}
