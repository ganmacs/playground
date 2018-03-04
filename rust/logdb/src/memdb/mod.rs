extern crate bytes;
extern crate rand;

use std::iter::{Iterator, IntoIterator};
use batch::KeyKind;
mod skiplist;

pub use ikey::InternalKey;
pub use bytes::{Bytes, LittleEndian, ByteOrder};

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
        // let v = key.memtable_key();
        let v = key.user_key();
        self.inner.get(&v)
    }

    pub fn add(&mut self, key_kind: KeyKind, ukey: &Bytes, value: &Bytes) {
        let n = ukey.len();
        let mut buf = [0; 4];
        LittleEndian::write_u32(&mut buf, n as u32);
        // let mut key = Bytes::from(buf.to_vec());
        // key.extend(Bytes::from(ukey));

        match key_kind {
            KeyKind::SET => self.inner.insert(ukey, &value),
            KeyKind::DELETE => (),    // TODO
        };
    }
}

impl IntoIterator for MemDB {
    type Item = (Bytes, Bytes);
    type IntoIter = MemDBIterator;

    fn into_iter(self) -> Self::IntoIter {
        MemDBIterator { inner: self.inner.into_iter() }
    }
}

pub struct MemDBIterator {
    inner: skiplist::SkipListIterator,
}

impl Iterator for MemDBIterator {
    type Item = (Bytes, Bytes);

    fn next(&mut self) -> Option<Self::Item> {
        self.inner.next()
    }
}

#[cfg(test)]
mod tests {
    use super::{MemDB, Bytes, InternalKey, KeyKind};

    #[test]
    fn test_skiplist() {
        let mut db = MemDB::new();

        let hash = vec![
            ("key", Bytes::from("value")),
            ("key1", Bytes::from("value1")),
            ("key2", Bytes::from("value2")),
            ("key3", Bytes::from("value3")),
            ("key4", Bytes::from("value4")),
            ("key5", Bytes::from("value5")),
            ("key6", Bytes::from("value___6")),
            ("key77", Bytes::from("value   7")),
        ];

        for v in hash {
            db.add(KeyKind::SET, &Bytes::from(v.0), &v.1);
            assert_eq!(db.get(&InternalKey::new(&v.0, 0)).unwrap(), v.1);
        }

        assert_eq!(db.get(&InternalKey::new("notfound", 0)), None);
    }


    #[test]
    fn test_skiplist_iter() {
        let mut db = MemDB::new();

        let mut hash: Vec<(&str, Bytes)> = vec![
            ("key", Bytes::from("value")),
            ("key1", Bytes::from("value1")),
            ("key2", Bytes::from("value2")),
            ("key3", Bytes::from("value3")),
            ("key4", Bytes::from("value4")),
            ("key5", Bytes::from("value5")),
            ("key6", Bytes::from("value___6")),
            ("key77", Bytes::from("value   7")),
        ];

        for v in &hash.clone() {
            db.add(KeyKind::SET, &Bytes::from(v.0), &v.1);
        }

        let mut it = db.into_iter();
        for v in hash.into_iter() {
            assert_eq!(it.next().unwrap(), (Bytes::from(v.0), v.1));
        }

    }
}
