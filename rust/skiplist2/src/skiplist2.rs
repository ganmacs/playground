use rand;
use rand::Rng;
use bytes::Bytes;
use std::cmp::Ordering;
use byteorder::{ByteOrder, LittleEndian};

const DATA_SIZE: usize = 8192;
const MAX_HEIGHT: usize = 7;

pub trait Comparator {
    fn compare(&self, a: &Bytes, b: &Bytes) -> Ordering;
}

impl Comparator for InternalKeyComparator {
    fn compare(&self, a: &Bytes, b: &Bytes) -> Ordering {
        match extract_user_key(a).cmp(extract_user_key(b)) {
            Ordering::Equal => {
                let a_s = a.len();
                let b_s = b.len();
                LittleEndian::read_u64(&b[b_s - 8..b_s])
                    .cmp(&LittleEndian::read_u64(&a[a_s - 8..a_s]))
            }
            t => t,
        }
    }
}

fn extract_user_key<'a>(key: &'a Bytes) -> &'a [u8] {
    let size = key.len();
    &key[0..size - 8]
}

pub struct InternalKeyComparator;

#[derive(Debug)]
pub struct SkipList<T> {
    data: Bytes,
    index: Vec<SkipValueIndex>,
    cmp: T,
}

impl<T: Comparator> SkipList<T> {
    pub fn new(c: T) -> Self {
        SkipList {
            data: Bytes::with_capacity(DATA_SIZE),
            index: vec![SkipValueIndex::new(0, 0, 0)],
            cmp: c,
        }
    }

    pub fn empty(&self) -> bool {
        self.data.len() == 0
    }

    pub fn seek(&self, key: &Bytes) -> Option<Bytes> {
        let sv = self.find_greater_than_eq(key, &mut None);
        if sv.id == self.head().id {
            None
        } else {
            Some(self.load(sv))
        }
    }

    pub fn insert(&mut self, key: Bytes) {
        let mut prev = [0; MAX_HEIGHT];
        let _ = {
            self.find_greater_than_eq(&key, &mut Some(&mut prev));
        };

        let new_index = self.index.len();
        let mut new_v = SkipValueIndex::new(new_index, self.data.len(), key.len());
        self.store(key);

        let height = rand::thread_rng().gen_range(1, MAX_HEIGHT);
        for level in 0..height {
            let i = prev[level];
            let next_i = self.index[i].next(level);
            self.index[i].set_next(level, new_index as u16);
            new_v.set_next(level, next_i as u16);
        }

        self.index.push(new_v);
    }

    fn find_greater_than_eq(
        &self,
        key: &Bytes,
        prev: &mut Option<&mut [usize; MAX_HEIGHT]>,
    ) -> &SkipValueIndex {
        let mut level = MAX_HEIGHT;
        let mut sv: &SkipValueIndex = self.head();
        let mut next = self.head();

        while level > 0 {
            next = &self.index[sv.next(level - 1)];
            if next.id == self.head().id {
                prev.as_mut().map(|p| p[level - 1] = sv.id);
                level -= 1;
            } else {
                if self.cmp.compare(key, &self.load(&next)) == Ordering::Greater {
                    sv = next;
                } else {
                    prev.as_mut().map(|p| p[level - 1] = sv.id);
                    level -= 1;
                }
            }
        }
        next
    }

    fn head(&self) -> &SkipValueIndex {
        &self.index[0]
    }

    fn load(&self, sr: &SkipValueIndex) -> Bytes {
        self.data.slice(sr.idx, sr.idx + sr.size)
    }

    fn store(&mut self, sr: Bytes) {
        self.data.extend(sr);
    }

    fn iter<'a>(&'a self) -> SkipListIterator<'a, T> {
        SkipListIterator {
            pos: 0,
            inner: &self,
        }
    }
}

// INDEX data format
#[derive(Debug, Clone)]
struct SkipValueIndex {
    pub id: usize,
    pub size: usize,
    pub idx: usize,
    nexts: [u16; MAX_HEIGHT],
}

impl SkipValueIndex {
    pub fn new(id: usize, idx: usize, size: usize) -> Self {
        Self {
            id,
            idx,
            size,
            nexts: [0; MAX_HEIGHT],
        }
    }

    pub fn next(&self, level: usize) -> usize {
        self.nexts[level] as usize
    }

    pub fn set_next(&mut self, level: usize, v: u16) {
        self.nexts[level] = v;
    }
}

pub struct SkipListIterator<'a, T: 'a> {
    inner: &'a SkipList<T>,
    pos: usize,
}

impl<'a, T: Comparator> Iterator for SkipListIterator<'a, T> {
    type Item = Bytes;

    fn next(&mut self) -> Option<Self::Item> {
        let next_id = self.inner.index[self.pos].next(0); // level 0
        self.pos = next_id;

        let ref next = self.inner.index[next_id];
        if next.id == self.inner.head().id {
            None
        } else {
            Some(self.inner.load(next))
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    struct TestKeyComparator;

    impl Comparator for TestKeyComparator {
        fn compare(&self, a: &Bytes, b: &Bytes) -> Ordering {
            a.cmp(b)
        }
    }

    #[test]
    fn skiplist_set_and_get_test() {
        let mut sl = SkipList::new(TestKeyComparator);

        for i in 0..100 {
            let key = Bytes::from(format!("key{:?}", i));
            sl.insert(key.clone());
            assert_eq!(sl.seek(&key), Some(key))
        }
    }

    #[test]
    fn skiplist_iterator_value_is_ordered() {
        let mut sl = SkipList::new(TestKeyComparator);

        let keys: Vec<Bytes> = (0..10)
            .map(|v: usize| Bytes::from(format!("key{:?}", v)))
            .collect();

        {
            keys.clone().reverse();
            for k in keys.iter() {
                sl.insert(k.clone())
            }
        }

        for (a, b) in sl.iter().zip(keys) {
            assert_eq!(a, b);
        }
    }
}
