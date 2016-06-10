extern crate getopts;

mod config;
mod ex;
mod options;
mod file;
mod dir;

fn main() {
    ex::Ex::new().run();
}
