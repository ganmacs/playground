use std::collections::HashSet;

fn main() {
    let mut a: HashSet<i32> = vec!(1i32, 2, 3).into_iter().collect();
    assert!(a.insert(4));
    assert!(a.(4));

    println!("{:?}", a);
}
