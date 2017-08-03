extern crate x86_32;

use std::env;
use x86_32::errors::Error;
use x86_32::emulator;

fn main() {
    let status = match get_file_name() {
        Err(v) => {
            println!("{:?}", v);
            1
        }
        Ok(v) => {
            match run(v) {
                Err(v) => {
                    println!("{:?}", v);
                    1
                }
                _ => 0,
            }
        }
    };

    std::process::exit(status)
}

fn run(v: String) -> Result<(), Error> {
    println!("{:?}", v);
    emulator::run(v)
}


fn get_file_name() -> Result<String, &'static str> {
    let args: Vec<_> = env::args().skip(1).collect();
    if args.len() <= 0 {
        Err("Usage: x86_32 <filename>")
    } else {
        Ok(args[0].to_owned())
    }
}
