use std::process;
use file::File;
use dir::Dir;
use options::Options;
use getopts;

pub struct Config {
    paths: Vec<String>
}

impl Config {
    pub fn with_args() -> Self {
        match Options::parse() {
            Ok(matches) => {
                Config {
                    paths: matches.free,
                    mode: Mode::new(matches)
                }
            }
            Err(e) => {
                println!("{}", e);
                process::exit(e.exit_code());
            }
        }
    }
}

enum Mode {
    Details,
    Lines,
    Grid,
}

impl Mode {
    pub fn new(matches: getopts::Matches) {
    }
}
