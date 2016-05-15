extern crate getopts;

mod options;
mod file;
mod dir;

use std::env;
use std::process;
use std::path::Path;
use options::{Options, ErrStat};
use dir::Dir;
use file::File;

fn main() {
    match option_parse() {
        Err(e) => {
            println!("{}", e);
            process::exit(e.exit_code());
        },
        Ok((opts, paths)) => exec(opts, paths),
    }
}

fn exec(opts: Options, paths: Vec<String>)  {
    match collect(opts, paths) {
        Ok((dir, files)) => pretty_print(dir, files),
        Err(e) => println!("{:?}", e)
    }
}

fn pretty_print(dirs: Vec<Dir>, files: Vec<File>) {
}

fn option_parse() -> Result<(Options, Vec<String>), ErrStat>{
    let commands: Vec<String> = env::args().collect();
    let args: Vec<String> = commands.iter().cloned().skip(1).collect();
    Options::parse(&args)
}

fn collect(options: Options, mut paths: Vec<String>) -> Result<(Vec<Dir>, Vec<File>), String> {
    let mut files: Vec<File> = Vec::new();
    let mut dirs: Vec<Dir> = Vec::new();

    if paths.is_empty() {
        paths.push(".".to_owned());
    }

    for path in paths.iter() {
        match File::from_path(&Path::new(&path)) {
            Err(e) => {
                println!("{} {}", path, e)
            },
            Ok(f) => {
                if f.is_dirctory() {
                    match f.to_dir() {
                        Ok(d) => dirs.push(d),
                        Err(e) => println!("{}: {}", path, e)
                    }
                } else {
                    files.push(f);
                }
            }
        }
    }
    Ok((dirs, files))
}
