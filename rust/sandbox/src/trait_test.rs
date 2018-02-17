use std::cmp::Ordering;
use std::fmt;

pub trait Token {
    type V;

    fn value(&self) -> u64;
}

impl<T> fmt::Debug for Token<V = T> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Token({:?})", self.value())
    }
}

impl<T> PartialOrd for Token<V = T> {
    fn partial_cmp(&self, other: &Token<V = T>) -> Option<Ordering> {
        Some(self.value().cmp(&other.value()))
    }
}

impl<T> PartialEq for Token<V = T> {
    fn eq(&self, other: &Token<V = T>) -> bool {
        self.value() == other.value()
    }
}
pub struct IntegerToken {
    value: u64,
}

impl IntegerToken {
    pub fn new(v: u64) -> Self {
        IntegerToken { value: v }
    }
}

impl Token for IntegerToken {
    type V = u64;

    fn value(&self) -> u64 {
        self.value as u64
    }
}

pub fn run() {
    test1();
}

fn test1() {
    let t1 = IntegerToken::new(1);
    let t2 = IntegerToken::new(1);
    is_eq(&t1, &t2);
    // ppp(&1);
}


// fn ppp<T: Token>(t1: &T) {
//     println!("{:?}", t1);
// }

fn is_eq<T: Token>(t1: &T, t2: &T) {
    assert!(t1 == t2);
}
