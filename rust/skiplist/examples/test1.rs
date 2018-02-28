extern crate skiplist;

use skiplist::{MemDB, InternalKey, KeyKind, Bytes};

fn main() {
    let mut a = MemDB::new();
    let k0 = InternalKey::new("key0", 000);
    let v0 = Bytes::from("value0");
    a.add(KeyKind::SET, k0.user_key(), v0);

    let k1 = InternalKey::new("key1", 000);
    let v1 = Bytes::from("value1");
    a.add(KeyKind::SET, k1.user_key(), v1);

    let k2 = InternalKey::new("key2", 000);
    let v2 = Bytes::from("value2");
    a.add(KeyKind::SET, k2.user_key(), v2);

    let k3 = InternalKey::new("key3", 000);
    let v3 = Bytes::from("value3");
    a.add(KeyKind::SET, k3.user_key(), v3);

    let k4 = InternalKey::new("key4", 000);
    let v4 = Bytes::from("value4");
    a.add(KeyKind::SET, k4.user_key(), v4);

    println!("{:?}", a.get(&k0));
    println!("{:?}", a.get(&k1));
    println!("{:?}", a.get(&k2));
    println!("{:?}", a.get(&k3));
    println!("{:?}", a.get(&k4));
}
