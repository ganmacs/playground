use std::fmt::Debug;
use std::fs;
use std::io;
use std::io::{BufReader, Seek};

use std::ops::{Deref, DerefMut};

#[derive(Debug)]
struct B(usize);

impl Deref for B {
    type Target = usize;

    fn deref(&self) -> &usize {
        &self.0
    }
}

impl DerefMut for B {
    fn deref_mut(&mut self) -> &mut usize {
        &mut self.0
    }
}

#[derive(Debug)]
struct B2<'a>(&'a u64);

impl<'a> B2<'a> {
    pub fn add(&mut self) {
        // let mut a = &mut **self;
        // *a += 10;
    }
}

struct B3(Box<u64>);

impl B3 {
    pub fn add(&mut self) {
        *self.0 += 1;
    }
}

impl Deref for B3 {
    type Target = u64;

    fn deref(&self) -> &u64 {
        &*self.0
    }
}

impl DerefMut for B3 {
    fn deref_mut(&mut self) -> &mut u64 {
        &mut *self.0
    }
}

// impl<'a> Deref for B2<'a> {
//     type Target = u64;

//     fn deref(&self) -> &u64 {
//         &self.0
//     }
// }

// impl<'a> DerefMut for B2<'a> {
//     fn deref_mut(&mut self) -> &mut u64 {
//         &mut self.0
//     }
// }

struct A<'a, T: 'a> {
    inner: &'a T,
}

pub fn main() {
    // test1()
    // test2()
    // test3();
    // test4();
    test5();
}

fn test5() {
    let mut i = 10;
    let mut b = B3(Box::new(i));
    println!("{:?}, b={:?}", i, b.0);

    *b += 1;

    println!("{:?}", i);
    println!("{:?}, b={:?}", i, b.0);
}

fn test4() {
    let i = 10;
    let mut b1 = B(10);
    println!("b1 before {:?}", b1);
    b(&mut b1);

    println!("b1 after {:?}", b1);

    let mut b2 = B2(&i);
    println!("b2={:?},i={:?}", b2, i);
    b2.add();
    println!("{:?}", i);

    println!("-------------------------------");
    // b22(&mut b2);
}

// fn b22(b: &mut B2) {
//     **b += 1;
// }

fn b(i: &mut B) {
    **i += 1
}

fn test1() {
    let mut i = 10;
    println!("{:?}", i);
    a(&mut i);
    println!("{:?}", i);
}

fn a(i: &mut usize) {
    *i = 1;
}

fn test2() {
    let mut owner = Owner(18);
    owner.add_one();
    owner.print();
}

struct Owner(i32);

impl Owner {
    fn add_one(&mut self) {
        self.0 += 1
    }

    fn print<'a>(&'a self) {
        println!("`print`: {}", self.0);
    }
}

#[derive(Debug)]
struct Ref<'a, T: 'a>(&'a T);

fn print<T>(t: T)
where
    T: Debug,
{
    println!("`print`: t is {:?}", t);
}

fn print_ref<'a, T>(t: &'a T)
where
    T: Debug + 'a,
{
    println!("`print_ref`: t is {:?}", t);
}

fn test3() {
    let x = 7;
    let ref_x = Ref(&x);

    print_ref(&ref_x);
    print(ref_x);
}
