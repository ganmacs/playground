use std::fmt::{Debug, Display};

fn m_prints<T: Debug + Display>(t: &T) {
    println!("{:?}", t);
    println!("{}", t);
}


fn main() {
    let a = "asfd";
    m_prints(&a);
}
