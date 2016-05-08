use options::Option;
use std::fs;

mod options;

fn main() {
    let a = Option::new();
    println!("{:?}", a);
    println!("{:?}", Some(false));

    match fs::metadata("Cargo.toml") {
        Ok(meta) => {
            println!("{:?}", meta.permissions())
        }
        Err(err) => println!("{}", err),
    }
}
