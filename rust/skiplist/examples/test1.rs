extern crate skiplist;

fn main() {
    let mut a = skiplist::new();
    a.insert(b"key".to_vec(), b"value".to_vec());
    a.insert(b"key1".to_vec(), b"value2".to_vec());
    a.insert(b"key2".to_vec(), b"value3".to_vec());

    println!("{:?}", a.get(&b"key".to_vec()));
}
