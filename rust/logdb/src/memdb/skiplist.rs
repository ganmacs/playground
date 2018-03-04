use rand;
use rand::Rng;
use bytes::{Bytes, BytesMut, BufMut, LittleEndian, ByteOrder};
use super::MAX_HEIGHT;

type Key = Bytes;
type Value = Bytes;
type IdxFragment = [u8; 14];

#[derive(Debug)]
pub struct SkipList {
    data: Bytes,
    idx: SkipIndex,
}

const DATA_SIZE: usize = 4096;

impl SkipList {
    pub fn new() -> Self {
        SkipList {
            data: Bytes::with_capacity(DATA_SIZE),
            idx: SkipIndex::with_capacity(DATA_SIZE),
        }
    }

    pub fn get(&self, key: &Key) -> Option<Bytes> {
        let (n, exact) = self.find_greater_than_eq(key, &mut None);
        if exact {
            let offset = self.idx.val(n);
            Some(self.load(offset))
        } else {
            None
        }
    }

    pub fn insert(&mut self, key: &Key, value: &Value) {
        let mut prev = [HEAD; 12];
        let (n, exact) = self.find_greater_than_eq(key, &mut Some(&mut prev));

        if exact {
            let voffset = self.save(value.as_ref());
            self.idx.update_val(n, voffset as u8);
            return;
        }

        let mut ibuilder = IndexBuilder::new();

        let n1 = self.idx.len();
        let koffset = self.save(key.as_ref());
        ibuilder.key(koffset as u8);
        let voffset = self.save(value.as_ref());
        ibuilder.value(voffset as u8);

        let height = rand::thread_rng().gen_range(1, MAX_HEIGHT);

        for level in 0..height {
            let p = prev[level];
            let next_i = self.idx.next(p + level);
            ibuilder.next(level, next_i as u8);
            self.idx.update_next(p + level, n1 as u8);
        }

        self.idx.extend_from_slice(&ibuilder.build());
    }

    pub fn find_greater_than_eq(
        &self,
        key: &Key,
        prev: &mut Option<&mut [usize; 12]>,
    ) -> (usize, bool) {
        let mut level = MAX_HEIGHT - 1;
        let mut i = 0;
        let mut exact;
        let mut n;

        loop {
            n = self.idx.next(i + level);
            loop {
                if n == HEAD {
                    exact = false;
                    break;
                }

                let k = self.load(self.idx.key(n));
                let cmp = k >= key;
                if cmp {
                    exact = k == key;
                    break;
                }

                i = n;
                n = self.idx.next(i + level);
            }

            if let Some(v) = prev.as_mut() {
                v[level] = i;
            }

            if level == 0 {
                return (n, exact);
            }

            level -= 1;
        }
    }

    fn save(&mut self, v: &[u8]) -> usize {
        let len = v.len();
        let mut buf = BytesMut::with_capacity(len + 4);

        let offset = self.data.len();
        buf.put_u64::<LittleEndian>(len as u64);
        buf.put_slice(v);

        self.data.extend(buf);
        offset
    }

    fn load(&self, i: usize) -> Bytes {
        let u64_offset = i + 8;
        let buf = self.data.slice(i, u64_offset);
        let v = LittleEndian::read_u64(&buf) as usize;
        self.data.slice(u64_offset, u64_offset + v)
    }
}

// INDEX data format
// | KEY_i | VAL_i | NEXT_i_0 | NEXT_i_1 | ... | NEXT_i_11 | KEY_(i+1) | VAL_(i+1) | NEXT_(i+1)_0 |
const KEY: usize = 0;
const VAL: usize = 1;
const NEXT: usize = 2;

const HEAD: usize = 0;

#[derive(Debug)]
struct IndexBuilder {
    inner: IdxFragment,
}

impl IndexBuilder {
    pub fn new() -> Self {
        IndexBuilder { inner: [HEAD as u8; 14] }
    }

    pub fn key(&mut self, v: u8) -> &Self {
        self.inner[KEY] = v;
        self
    }

    pub fn value(&mut self, v: u8) -> &Self {
        self.inner[VAL] = v;
        self
    }

    pub fn next(&mut self, i: usize, v: u8) -> &Self {
        self.inner[i + NEXT] = v;
        self
    }

    pub fn build(&self) -> IdxFragment {
        self.inner
    }
}

#[derive(Debug)]
struct SkipIndex {
    inner: Vec<u8>,
}

impl SkipIndex {
    pub fn with_capacity(cap: usize) -> Self {
        let mut skip = SkipIndex { inner: Vec::with_capacity(cap) };
        skip.extend_from_slice(&IndexBuilder::new().build());
        skip
    }

    pub fn extend_from_slice(&mut self, slice: &IdxFragment) {
        self.inner.extend_from_slice(slice);
    }

    pub fn len(&self) -> usize {
        self.inner.len()
    }

    pub fn key(&self, i: usize) -> usize {
        self.inner[i + KEY] as usize
    }

    pub fn val(&self, i: usize) -> usize {
        self.inner[i + VAL] as usize
    }

    pub fn next(&self, i: usize) -> usize {
        self.inner[i + NEXT] as usize
    }

    pub fn update_key(&mut self, i: usize, v: u8) {
        self.inner[i + KEY] = v
    }

    pub fn update_val(&mut self, i: usize, v: u8) {
        self.inner[i + VAL] = v
    }

    pub fn update_next(&mut self, i: usize, v: u8) {
        self.inner[i + NEXT] = v
    }
}

pub struct SkipListIterator {
    pos: usize,
    idx: SkipIndex,
    inner: Bytes,
}

impl Iterator for SkipListIterator {
    type Item = (Key, Value);

    fn next(&mut self) -> Option<Self::Item> {
        self.pos = self.next_0();
        if self.pos == HEAD {
            return None;
        }

        let vi = self.idx.val(self.pos);
        let ki = self.idx.key(self.pos);
        Some((self.load(ki), self.load(vi)))
    }
}


impl SkipListIterator {
    fn next_0(&self) -> usize {
        self.idx.next(self.pos)
    }

    // TODO
    fn load(&self, i: usize) -> Bytes {
        let u64_offset = i + 8;
        let buf = self.inner.slice(i, u64_offset);
        let v = LittleEndian::read_u64(&buf) as usize;
        self.inner.slice(u64_offset, u64_offset + v)
    }
}

impl IntoIterator for SkipList {
    type Item = (Key, Value);
    type IntoIter = SkipListIterator;

    fn into_iter(self) -> Self::IntoIter {
        SkipListIterator {
            pos: 0,
            idx: self.idx,
            inner: self.data,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::{SkipList, Bytes};

    #[test]
    fn test_skiplist() {
        let mut list = SkipList::new();

        let hash = vec![
            (Bytes::from("key"), Bytes::from("value")),
            (Bytes::from("key1"), Bytes::from("value1")),
            (Bytes::from("key2"), Bytes::from("value2")),
            (Bytes::from("key3"), Bytes::from("value3")),
            (Bytes::from("key4"), Bytes::from("value4")),
            (Bytes::from("key5"), Bytes::from("value5")),
            (Bytes::from("key6"), Bytes::from("value___6")),
            (Bytes::from("key77"), Bytes::from("value   7")),
        ];

        for v in hash {
            list.insert(&v.0, &v.1);
            assert_eq!(list.get(&v.0).unwrap(), v.1);
        }

        assert_eq!(list.get(&Bytes::from("notfound")), None);
    }

    #[test]
    fn test_skiplist_iter() {
        let mut list = SkipList::new();

        let hash = vec![
            (Bytes::from("key"), Bytes::from("value")),
            (Bytes::from("key1"), Bytes::from("value1")),
            (Bytes::from("key2"), Bytes::from("value2")),
            (Bytes::from("key3"), Bytes::from("value3")),
            (Bytes::from("key4"), Bytes::from("value4")),
            (Bytes::from("key5"), Bytes::from("value5")),
            (Bytes::from("key6"), Bytes::from("value___6")),
            (Bytes::from("key77"), Bytes::from("value   7")),
        ];

        for v in &hash.clone() {
            list.insert(&v.0, &v.1);
        }

        let mut it = list.into_iter();
        assert_eq!(it.next().as_ref(), hash.get(0));
        assert_eq!(it.next().as_ref(), hash.get(1));
        assert_eq!(it.next().as_ref(), hash.get(2));
        assert_eq!(it.next().as_ref(), hash.get(3));
        assert_eq!(it.next().as_ref(), hash.get(4));
        assert_eq!(it.next().as_ref(), hash.get(5));
        assert_eq!(it.next().as_ref(), hash.get(6));
        assert_eq!(it.next().as_ref(), hash.get(7));
        assert_eq!(it.next().as_ref(), None);
    }
}
