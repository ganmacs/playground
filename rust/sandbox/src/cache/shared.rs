use super::SHARED_BIT;
use fasthash::murmur2;

use bytes::Bytes;

pub struct A {}

impl A {
    pub fn insert(&mut self, key: &Bytes, value: &Bytes, hash: u32) {}
}

pub struct SharedCache {
    caches: Vec<A>, // SOULD be fixed size
}

impl SharedCache {
    pub fn new() -> Self {
        let mut caches = vec![];
        for _ in 0..(1 << SHARED_BIT) {
            caches.push(A {});
        }
        Self { caches: caches }
    }

    pub fn insert(&mut self, key: &Bytes, value: &Bytes) {
        let h = SharedCache::hash(&key.to_vec());
        self.caches[SharedCache::shared(h)].insert(key, value, h);
    }

    fn shared(v: u32) -> usize {
        return (v as usize) >> (32 - SHARED_BIT);
    }

    fn hash(key: &Vec<u8>) -> u32 {
        murmur2::hash32(key)
    }
}

pub fn main() {
    let c = SharedCache::new();
    let k = Bytes::from("key1");
    let v = Bytes::from("value");
    c.insert(&k, &v);
}
