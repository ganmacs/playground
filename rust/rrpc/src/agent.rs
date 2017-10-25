use config::Config;

use codec::JsonCodec;

use futures::{Future, Stream, Sink};
use tokio_core::reactor::Core;
use tokio_core::net::TcpListener;
use tokio_io::AsyncRead;
use tokio_io::io::read_to_end;

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
    // let peers = config.peers();

    // for peer_addr in peers.iter() {
    //     let client = TcpStream::connect(&peer_addr, &handle);
    //     let request = client.and_then(|sock| tokio_io::io::write_all(sock, b"this is a client"));

    //     let a = request
    //         .and_then(|(sock, _request)| {
    //                       tokio_io::io::read_to_end(sock, Vec::new());
    //                       Ok(())
    //                   })
    //         .map_err(|e| panic!("{:?}", e));
    //     handle.clone().spawn(a);
    // }


    let listener = socket
        .incoming()
        .for_each(move |(socket, _addr)| {
                      let (_tx, rx) = socket.framed(JsonCodec).split();
                      let v = rx.into_future().then(|s| Ok(()));
                      handle.spawn(v);

                      Ok(())
                  });
    let _ = core.run(listener);
}
