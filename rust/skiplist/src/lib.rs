extern crate bytes;
extern crate rand;

mod node_arena;
mod node;
mod fixed_list;
mod skiplist;
mod ikey;

pub use ikey::InternalKey;
pub use bytes::{Bytes, LittleEndian, ByteOrder};

pub enum KeyKind {
    SET,
    DELETE,
}

const MAX_HEIGHT: usize = 12;

pub struct MemDB {
    inner: skiplist::SkipList,
}

impl MemDB {
    pub fn new() -> Self {
        MemDB { inner: skiplist::SkipList::new() }
    }

    // Should be LookupKey
    pub fn get(&self, key: &InternalKey) -> Option<Bytes> {
        let v = key.memtable_key();
        self.inner.get(&v)
    }

    pub fn add(&mut self, key_kind: KeyKind, ukey: Bytes, value: Bytes) {
        let n = ukey.len();
        let mut buf = [0; 4];
        LittleEndian::write_u32(&mut buf, n as u32);
        let mut key = Bytes::from(buf.to_vec());
        key.extend(ukey);

        match key_kind {
            KeyKind::SET => self.inner.insert(&key, &value),
            KeyKind::DELETE => (),    // TODO
        };
    }
}
