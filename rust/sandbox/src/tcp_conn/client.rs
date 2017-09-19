use std::str;
use std::net::TcpStream;
use std::io::{Write, Read};

pub struct Client {
    conn: TcpStream,
}

impl Client {
    pub fn new(addr: &'static str) -> Self {
        Client { conn: TcpStream::connect(addr).unwrap() }
    }

    pub fn exec(&mut self, msg: &'static str) {
        let _ = self.conn.write(msg.as_bytes());

        let mut v = [0u8; 1024];
        let s = self.conn.read(&mut v).unwrap();

        println!("Client recieved {:?}",
                 str::from_utf8(&v[0..s]).expect("Error at response"));
    }
}
