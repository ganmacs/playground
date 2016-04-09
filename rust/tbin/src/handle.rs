use std::io::prelude::*;
use std::fs::File;


fn setup() -> std::io::Result<()> {
    let mut a = try!(File::create("a"));
    a.write_all(b"grape")
}

fn main() {
    setup().unwrap();
}
