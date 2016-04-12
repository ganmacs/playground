use std::io::{self, Write};
use std::default::Default;
use std::collections::HashMap;
use std::ops::Add;

#[derive(Copy, Clone, PartialEq, Eq, Hash, Debug)]
pub struct Vec2 {
    pub x: i32,
    pub y: i32,
}

impl Vec2 {
    pub fn new(x: i32, y: i32) -> Vec2 {
        Vec2 {
            x: x,
            y: y,
        }
    }
}

impl Add for Vec2 {
    type Output = Vec2;
    fn add(self, rhs: Vec2) -> Vec2 {
        Vec2 {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
        }
    }
}

// extern crate collections;
// use std::collections::range::RangeArgument;
// use self::collections::range::RangeArgument;

fn main() {
    let stdout = io::stdout();
    let mut arguments = std::env::args().skip(1);
    let mut stdout = stdout.lock();
    match stdout.write(b"asdf") {
        Ok(x) => println!("{:?}", x),
        Err(x) => println!("{:?}", x),
    }

    let e = std::io::Error::new(std::io::ErrorKind::AlreadyExists, "no no no");
    // let eee: io::Result<()> = Err(e);
    // try!(Err(e));
    // println!("{:?}", eee.try(1));


    let path = "main.rs";
    let p = std::path::Path::new(&path);
    // Err("asdf").try("asdf");

    // if let Some(p) = p.file_name() {
    //     println!("{:?}", p);
    // }


    if let Some(arg) = arguments.next() {
        println!("{:?}", arg);
    }


    let a = Some(10);
    println!("{:?}", a.unwrap_or(11));
    let a = [1; 32];
    println!("{:?}", a);

    // let a: Range<i32> = 0..1;
    // println!("{:?}", a);
    // println!("{:?}", );

    let a = Vec2::new(10, 11);
    let b = Vec2::new(12, 1);
    println!("{:?}", a+b);

    let mut h = HashMap::new();
    h.insert("asf", 1);
    let a = match h.get("asf") {
        Some(&v) => v,
        None => 2,
    };

    println!("{:?}", a);
    let i: i32 = Default::default();
    println!("{:?}", i);
}
