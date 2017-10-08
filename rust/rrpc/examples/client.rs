extern crate tokio_core;
extern crate tokio_timer;
extern crate tokio_io;
extern crate futures;
extern crate core;

use tokio_timer::*;
use tokio_core::reactor::Core;
use tokio_core::net::TcpStream;
use futures::*;

use std::io::{Write, Read};
use std::str;
use std::time::*;
use std::net::SocketAddr;

pub fn main() {
    let timer = Timer::default();
    let ticker = timer.interval(Duration::from_millis(1000));

    let mut core = Core::new().unwrap();
    let handle = core.handle();
    let addr = "127.0.0.1:3000".parse::<SocketAddr>().unwrap();

    let heartbeater = ticker
        .and_then(move |_| {
            let stream = TcpStream::connect(&addr, &handle);
            let request =
                stream.and_then(|sock| tokio_io::io::write_all(sock, b"this is a client"));

            request
                .and_then(|(sock, _request)| tokio_io::io::read_to_end(sock, Vec::new()))
                .map_err(|e| panic!("{:?}", e))
        })
        .for_each(|_| Ok(()));
    core.run(heartbeater).unwrap();
}

// response.and_then( |(sock, data)|{
//     println!("{}", String::from_utf8_lossy(&data))
//         Ok(())
// })

// let _ = stream.write(&[1, 1, 3]);
// let mut v = [0u8, 1024];
// let bs = stream.read(&mut v).unwrap();
// println!("Serever recieved {:?}",
//          str::from_utf8(&v[0..bs]).expect("Error at response"));
// Ok(())
