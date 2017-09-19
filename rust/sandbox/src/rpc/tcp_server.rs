use std::net::{TcpListener, TcpStream};
use std::io::{Read, Write};
use std::{time, thread, str};
use rand;

pub struct TcpServer {
    listener: TcpListener,
}

impl TcpServer {
    pub fn new(addr: &'static str) -> Self {
        TcpServer { listener: TcpListener::bind(addr).unwrap() }
    }

    pub fn start(&self) {
        info!("Starting server...");

        for stream in self.listener.incoming() {
            match stream {
                Ok(s) => {
                    thread::spawn(move || handle_client(s));
                }
                Err(msg) => println!("{:?}", msg),
            };
        }
    }
}

fn handle_client(mut stream: TcpStream) {
    info!("New client {}", stream.peer_addr().unwrap());
    let mut v = [0u8; 1024];

    loop {
        let bs = stream.read(&mut v).unwrap();
        println!("Serever recieved {:?}",
                 str::from_utf8(&v[0..bs]).expect("Error at response"));

        if bs < 1024 {
            let ret = format!("From echo server {:?}",
                              str::from_utf8(&v[0..bs]).expect("Error at response"));

            let n = rand::random::<(u64)>() % 10;
            let ten_millis = time::Duration::from_millis(1000 * n);
            thread::sleep(ten_millis);

            let size_write_bytes = stream.write(ret.as_bytes()).unwrap();

            if ret.len() != size_write_bytes {
                println!("{:?}", size_write_bytes);
                panic!("WTF");
            }
            break;
        }
    }
}
