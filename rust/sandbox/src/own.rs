use std::net::{SocketAddr, ToSocketAddrs};
use std::iter::Iterator;
use std::time;


pub struct Builder {
    addr: Option<Vec<SocketAddr>>,
}

pub struct Builder2 {
    addr: Box<Vec<SocketAddr>>,
}

pub struct Config {
    addr: Option<Vec<SocketAddr>>,
}

impl Builder {
    pub fn new() -> Self {
        Builder { addr: None }
    }

    pub fn addr<A: ToSocketAddrs>(mut self, addrs: A) -> Self {
        let k = addrs
            .to_socket_addrs()
            .map(|v| v.collect::<Vec<_>>())
            .unwrap();

        self.addr = Some(k);
        self
    }

    pub fn build(self) -> Config {
        Config { addr: self.addr }
    }
}

// impl Builder2 {
//     pub fn new() -> Self {
//         Builder2 { addr: Box::new(vec![]) }
//     }

//     pub fn addr<A: ToSocketAddrs>(mut self, addrs: A) -> Self {
//         let k = addrs
//             .to_socket_addrs()
//             .map(|v| v.collect::<Vec<_>>())
//             .unwrap();

//         // self.addr = self.addr.map(|_| k);
//         self
//     }

//     pub fn build(&mut self) -> Config {
//         Config { addr: self.addr }
//     }
// }

#[derive(Debug, Clone, Copy)]
struct A {}

impl A {
    pub fn foo(self) {
        println!("{:?}", "foo");
    }

    pub fn bar(self) {
        println!("{:?}", "bar");
    }
}


pub fn run() {
    let a = A {};
    // a.foo();
    // a.bar();
    // {
    // let a = vec![1, 2, 3];
    // let b = a;
    // println!("{:?}", a);
    // }

    {
        let a = 1;
        let b = a;
        println!("{:?}", a);
    }

    {
        let a = A {};
        let b = a;
        println!("{:?}", a);
    }

    {
        let addr = "192.0.0.1:8000".to_socket_addrs().unwrap();
        let a = addr.collect::<Vec<_>>();

    }

    let b = Builder::new();
    b.addr("192.0.0.1:8000").build();

}
