use config::Config;

use std::io::{Read, Write};
use std::str;


use futures::{Future, Stream};
use tokio_io;
use tokio_io::AsyncRead;
use tokio_io::io as tio;
use tokio_io::io::shutdown;

use tokio_core::reactor::Core;
use tokio_core::net::{TcpListener, TcpStream, TcpStreamNew};

pub struct Agent {
    config: Config,
}

impl Agent {
    // XXX return exit status
    pub fn run(c: Config) {
        let agent = Agent::new(c);
        agent.start();
    }

    pub fn new(config: Config) -> Self {
        Agent { config }
    }

    fn start(&self) {
        start(&self.config)
    }
}

fn start(config: &Config) {
    let mut core = Core::new().unwrap();
    let handle = core.handle();

    let socket = TcpListener::bind(&config.addr(), &handle).unwrap();
    let peers = config.peers();


    for peer_addr in peers.iter() {
        let server = TcpStream::connect(&peer_addr, &handle);
        let a = server
            .and_then(|sock| {
                          let (_, mut writer) = sock.split();
                          writer.write(b"hey");
                          shutdown(writer);
                          Ok(())
                      })
            .map(|_| println!("{:?}", "ok"))
            .map_err(|_| println!("{:?}", "ng"));

        handle.clone().spawn(a);
    }

    let listener = socket
        .incoming()
        .and_then(|(socket, _)| tio::read(socket, Vec::new()))
        .and_then( || )
    // .and_then(|(sock, buf, size)| {
    //               println!("{:?},{:?}", buf, size);
    //               Ok(())
    //           })
        .for_each(|(sock, buf, size)| {
            println!("{:?},{:?}", buf, size);
            Ok(())
        }
        );

    let _ = core.run(listener);



}

// println!("{:?}", "heihiehie");
// tokio_io::io::write_all(socket, b"Hello!\n");
// Ok(())
