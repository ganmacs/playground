extern crate tokio_core;
extern crate tokio_timer;
extern crate tokio_io;
extern crate futures;
extern crate core;
extern crate rrpc;
extern crate bytes;

use std::net::SocketAddr;
use tokio_core::reactor::Core;

pub fn main() {
    let mut core = Core::new().unwrap();
    let handle = core.handle();
    let addr = "127.0.0.1:8080".parse::<SocketAddr>().unwrap();

    let ping = codec_tcp::ping(&addr, &handle);
    core.run(ping).unwrap();
}

mod codec_tcp {
    use std::io;
    use std::net::SocketAddr;
    use rrpc::codec::JsonCodec;

    use futures::{Stream, Future};
    use tokio_core::net::TcpStream;
    use tokio_core::reactor::Handle;
    use tokio_io::AsyncRead;

    use heartbeater;

    pub fn ping(addr: &SocketAddr, handle: &Handle) -> Box<Future<Item = (), Error = io::Error>> {
        let handle = handle.clone();
        let tcp = TcpStream::connect(&addr, &handle);

        Box::new(tcp.map(move |sock| {
            let ticker = heartbeater::foo();

            let (sink, strm) = sock.framed(JsonCodec).split();

            let tic = ticker
                .forward(sink)
                .then(|ret| {
                          if let Err(e) = ret {
                              panic!("failed to write to socket: {}", e)
                          }
                          Ok(())
                      });


            handle.spawn(tic)
        }))

    }
}

mod heartbeater {
    use std::io;
    use std::time::*;

    use tokio_timer::Timer;
    use futures::Stream;
    use rrpc::message::Message;

    pub fn foo() -> Box<Stream<Item = Message, Error = io::Error>> {
        let timer = Timer::default();
        let ticker = timer.interval(Duration::from_millis(1000));

        Box::new(ticker
                     .map(|_| {
                              Message::Ping {
                                  id: 0,
                                  name: "foooo".to_owned(),
                                  from: "heihei".to_owned(),
                              }
                          })
                     .map_err(|e| panic!(e)))
    }

}
