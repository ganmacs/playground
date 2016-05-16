extern crate getopts;

mod ex;
mod options;
mod file;
mod dir;

use std::env;
use std::process;
use options::{Options, ErrStat};
use ex::Ex;

fn main() {
    match parse_option() {
        Ok((opts, paths)) => Ex { options: opts }.exec(paths),
        Err(e) => {
            println!("{}", e);
            process::exit(e.exit_code());
        },
    }
}

fn parse_option() -> Result<(Options, Vec<String>), ErrStat>{
    let commands: Vec<String> = env::args().collect();
    let args: Vec<String> = commands.iter().cloned().skip(1).collect();
    Options::parse(&args)
}
