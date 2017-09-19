#[derive(Debug)]
struct SSS<'a> {
    foo: &'a str,
}

impl<'a> SSS<'a> {
    pub fn new(s: &'a str) -> Self {
        SSS { foo: s }
    }
}

pub fn run() {
    let v = "asfd";
    s1(v);
    s2(v);
    let v3 = s3();
    println!("{:?}", v3);
    println!("{:?}", s4());

    {
        let i = init();
        println!("{:?}", i);
    }

    println!("-------------------------------");
}

fn init<'a>() -> SSS<'a> {
    SSS::new("asdf") // lifetime is static
}

fn s1(a: &str) {
    println!("{:?}", a);
}

fn s2(a: &str) -> &str {
    a
}

fn s3() -> &'static str {
    "foo"
}

// fn s31<'a>(k: &'a str) -> String {
//     k.to_string() + "asf"
// }

fn s4() -> String {
    String::from("foo")
}
