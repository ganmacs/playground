mod options;
mod ex;
mod file;

use std::env;
use std::process;
use options::Options;
use ex::Ex;

fn main() {
    let commands: Vec<String> = env::args().collect();
    let program: String = commands[0].clone();
    let args: Vec<String> = commands.iter().cloned().skip(1).collect();

    println!("{:?}", program);

    match Options::parse(&args) {
        Ok((opt, paths)) => {
            let ex = Ex { options: opt };
            ex.run(paths)
        },
        Err(e) => {
            println!("{}", e);
            process::exit(e.exit_code());
        }
    };
}
