mod options;

use std::env;
use std::process;
use options::Options;

struct Ex {
    options: Options
}

fn main() {
    let commands: Vec<String> = env::args().collect();
    let program: String = commands[0].clone();
    let args: Vec<String> = commands.iter().cloned().skip(1).collect();

    println!("{:?}", program);

    let k: Ex = match Options::parse(&args) {
        Ok(opt) => Ex { options: opt },
        Err(e) => {
            println!("{}", e);
            process::exit(e.exit_code());
        }
    };

    println!("{:?}", k.options.matches.opt_present("l"));
}
