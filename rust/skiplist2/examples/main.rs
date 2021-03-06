extern crate skiplist2;

use skiplist2::{Bytes, InternalKeyComparator, SkipList};

fn main() {
    let mut sl = SkipList::new(InternalKeyComparator);

    for i in 0..100 {
        let key = Bytes::from(format!("key{:?}", i));
        sl.insert(key.clone());
        println!("{:?}", sl.seek(&key));
    }
}
