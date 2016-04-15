extern crate osg;

use osg::ropt::Ropt;


const USAGE: &'static  str = "
foo bar hoge shoge
";

fn main() {
    let a = Ropt::new(USAGE)
        .and_then(|r| r.decode())
        .unwrap_or_else(|e| e.exit());
    println!("{:?}", a);

    // match  {
    //     Ok(x) => println!("{:?}", x),
    //     Err(x) => println!("{:?}", x),
    // }

    // if arguments.count() < 2 {
    //     let _ = &stderr.write(b"no arguments.");
    //     let _ = stderr.flush();
    // }


    // for arg in arguments {
    //     println!("{:?}", arg);
    // }
}
