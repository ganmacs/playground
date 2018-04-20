use rand;
use rand::Rng;
use bytes::Bytes;

type Key = Bytes;

const DATA_SIZE: usize = 8192;
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
            index: vec![SkipValueIndex::new(0, 0, 0)],
        }
    }

    pub fn empty(&self) -> bool {
        self.data.len() == 0
    }

    pub fn seek(&self, key: &Key) -> Option<Bytes> {
        let sv = self.find_greater_than_eq(key, &mut None);
        if sv.id == self.head().id {
            None
        } else {
            Some(self.load(sv))
        }
    }

    pub fn insert(&mut self, key: Key) {
        let mut prev = [0; 7];
        let sv = {
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
        key: &Key,
        prev: &mut Option<&mut [usize; 7]>,
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
                if self.load(&next) < key {
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

    fn store(&mut self, sr: Key) {
        self.data.extend(sr);
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
