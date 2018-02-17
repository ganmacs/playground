extern crate logdb;

// use logdb;

fn main() {
    let mut db = logdb::open("level");
    db.set("key1", "value2");

    println!("{:?}", db.get("key"));
    println!("{:?}", db.get("key1"));
}
