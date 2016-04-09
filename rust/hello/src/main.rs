// extern crate semver;

// use semver::Version;

fn main() {
    // assert!(Version::parse( "1.2.3.") == Ok(Version{
    //     major: 1,
    //     minor: 2,
    //     patch: 3,
    //     pre: vec!(),
    //     build: vec!(),
    // }));

    // println!("Versions compred successfully");

    // return 0;

    // let mut v = vec![];
    // v.push("hello");

    // let x = v[0].clone();
    // v.push("world");

    // println!("{}",x);

    for _ in range(0, 10) {
        spawn(proc() {
            println!("Hello, world!");
        });
    }
}
