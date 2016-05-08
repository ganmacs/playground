use std::fs::File;

fn main() {
    let a = File::open("Cargo.toml");
    println!("{:?}", a);
    println!("{:?}", 1);
}
