use std::fs;
use std::io;
use std::io::{BufReader, Seek};
use std::io::Read;

pub fn main() {
    let fd = fs::OpenOptions::new() // add read permission?
        .read(true)
        .open("b")
        .unwrap();

    let mut reader = BufReader::new(fd);

    let mut v = [0; 10];
    let ret = reader.read(&mut v);
    println!("{:?}", v);

    reader.seek(io::SeekFrom::Start(10));
    let ret = reader.read(&mut v);
    println!("{:?}", v);

    reader.seek(io::SeekFrom::Start(0));
    let ret = reader.read(&mut v);
    println!("{:?}", v);
}
