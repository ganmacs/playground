use std::collections::LinkedList;

use rand;
use rand::Rng;
use bytes::{BufMut, Bytes, BytesMut};
use byteorder::{ByteOrder, LittleEndian};

use std::cmp;

type Key = Bytes;
type IdxFragment = [u16; 14];

const DATA_SIZE: usize = 4096;
const MAX_HEIGHT: usize = 7;

#[derive(Debug)]
pub struct SkipList {
    data: Bytes,
    index: Vec<SkipValueIndex>,
}

impl SkipList {
    pub fn new() -> Self {
        SkipList {
            data: Bytes::with_capacity(DATA_SIZE),
            index: vec![SkipValueIndex::new(0, 0)],
        }
    }

    pub fn empty(&self) -> bool {
        self.data.len() == 0
    }

    pub fn seek(&self, key: &Key) -> Option<Bytes> {
        let sv = self.find_greater_than_eq(key, &mut None);
        if sv.idx == self.head().idx {
            None
        } else {
            Some(self.load(sv))
        }
    }

    pub fn insert(&self, key: &Key) {
        let mut prev = [0; 12];
        let sv = self.find_greater_than_eq(key, &mut Some(&mut prev));

        let height = MAX_HEIGHT;
        for level in 0..height {
            let p = prev[level];
            self.index[p];
            // let next_i = self.index.next(p);
            // ibuilder.next(level, next_i as u16);
            // self.idx.update_next(p + level, n1 as u16);
        }
    }

    fn head(&self) -> &SkipValueIndex {
        &self.index[0]
    }

    fn find_greater_than_eq(
        &self,
        key: &Key,
        prev: &mut Option<&mut [usize; 12]>,
    ) -> &SkipValueIndex {
        let mut level = MAX_HEIGHT;
        let mut sr: &SkipValueIndex = self.head();

        while level > 0 {
            let next = &self.index[sr.next(level - 1)];
            if next.idx == self.head().idx {
                level -= 1;
            } else {
                if self.load(&sr) < key {
                    sr = next;
                } else {
                    prev.as_mut().map(|p| p[level - 1] = sr.idx);
                    level -= 1;
                }
            }
        }
        sr
    }

    fn save(&mut self, v: &[u8]) -> usize {
        let len = v.len();
        let mut buf = BytesMut::with_capacity(len + 4);

        let offset = self.data.len();
        buf.put_u64_le(len as u64);
        buf.put_slice(v);

        self.data.extend(buf);
        offset
    }

    fn load(&self, sr: &SkipValueIndex) -> Bytes {
        self.data.slice(sr.idx, sr.idx + sr.size)
    }

    // pub fn insert(&mut self, key: &Key) {
    //     let mut prev = [HEAD; 12];
    //     let (n, exact) = self.find_greater_than_eq(key, &mut Some(&mut prev));

    //     if exact {
    //         let voffset = self.save(value.as_ref());
    //         println!(
    //             "Overwrite value {:?} to {:?} about key={:?}",
    //             self.idx.val(n),
    //             value,
    //             key
    //         );
    //         self.idx.update_val(n, voffset as u16);
    //         return;
    //     }

    //     let mut ibuilder = IndexBuilder::new();

    //     let n1 = self.idx.len();
    //     let koffset = self.save(key.as_ref());
    //     ibuilder.key(koffset as u16);
    //     let voffset = self.save(value.as_ref());
    //     ibuilder.value(voffset as u16);

    //     // let height = rand::thread_rng().gen_range(1, MAX_HEIGHT);
    //     let height = 12;

    //     for level in 0..height {
    //         let p = prev[level];
    //         let next_i = self.idx.next(p + level);
    //         ibuilder.next(level, next_i as u16);
    //         self.idx.update_next(p + level, n1 as u16);
    //     }

    //     self.idx.extend_from_slice(&ibuilder.build());
    // }
}

// INDEX data format
#[derive(Debug, Clone)]
struct SkipValueIndex {
    nexts: [u16; MAX_HEIGHT],
    pub size: usize,
    pub idx: usize,
}

impl SkipValueIndex {
    pub fn new(idx: usize, size: usize) -> Self {
        Self {
            nexts: [0; MAX_HEIGHT],
            idx,
            size,
        }
    }

    pub fn next(&self, level: usize) -> usize {
        self.nexts[level] as usize
    }

    pub fn set_next(&mut self, level: usize, v: u16) {
        self.nexts[level] = v;
    }
}

// pub struct SkipListIterator {
//     pos: usize,
//     idx: SkipIndex,
//     inner: Bytes,
// }

// impl Iterator for SkipListIterator {
//     type Item = (Key, Value);

//     fn next(&mut self) -> Option<Self::Item> {
//         self.pos = self.next_0();
//         if self.pos == HEAD {
//             return None;
//         }

//         let vi = self.idx.val(self.pos);
//         let ki = self.idx.key(self.pos);
//         Some((self.load(ki), self.load(vi)))
//     }
// }

// impl SkipListIterator {
//     fn next_0(&self) -> usize {
//         self.idx.next(self.pos)
//     }

//     // TODO
//     fn load(&self, i: usize) -> Bytes {
//         let u64_offset = i + 8;
//         let buf = self.inner.slice(i, u64_offset);
//         let v = LittleEndian::read_u64(&buf) as usize;
//         self.inner.slice(u64_offset, u64_offset + v)
//     }
// }

// impl IntoIterator for SkipList {
//     type Item = (Key, Value);
//     type IntoIter = SkipListIterator;

//     fn into_iter(self) -> Self::IntoIter {
//         SkipListIterator {
//             pos: 0,
//             idx: self.idx,
//             inner: self.data,
//         }
//     }
// }
