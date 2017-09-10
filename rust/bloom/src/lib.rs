use std::hash::{Hash, Hasher, BuildHasher};
use std::collections::hash_map::RandomState;

pub struct Bloom {
    bitmap: Vec<bool>,
    bit_size: u64,
    k: u64,
    hasher_builder: RandomState,
}

impl Bloom {
    pub fn new(m: usize, k: usize) -> Self {
        Self {
            bitmap: vec![false; m],
            bit_size: m as u64,
            k: k as u64,
            hasher_builder: RandomState::default(),
        }
    }

    pub fn set<T: Hash>(&mut self, item: &T) {
        let mut hasher = self.hasher_builder.build_hasher();

        for _ in 0..self.k {
            item.hash(&mut hasher);
            let h = (hasher.finish() % self.bit_size) as usize;
            self.bitmap[h] = true;
        }
    }

    pub fn check<T: Hash>(&mut self, item: &T) -> bool {
        let mut hasher = self.hasher_builder.build_hasher();

        for _ in 0..self.k {
            item.hash(&mut hasher);
            let h = (hasher.finish() % self.bit_size) as usize;
            if !self.bitmap[h] {
                return false;
            }

        }
        true
    }
}

#[test]
fn bloom_test_set() {
    let mut filter = Bloom::new(1000, 10);
    let key0 = "key0";
    let key1 = "key1";

    assert!(filter.check(&key0) == false);
    assert!(filter.check(&key1) == false);

    filter.set(&key0);
    filter.set(&key1);

    assert!(filter.check(&key0));
    assert!(filter.check(&key1));
}
