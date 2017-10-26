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
    let core = Core::new().unwrap();
    let handle = core.handle();
    let addr = "127.0.0.1:8080".parse::<SocketAddr>().unwrap();

    codec_tcp::ping(&addr, &handle, core);
}

mod codec_tcp {
    use std::io;
    use std::net::SocketAddr;
    use rrpc::codec::JsonCodec;

    use futures::{Stream, Future};
    use tokio_core::net::TcpStream;
    use tokio_core::reactor::Handle;
    use tokio_io::AsyncRead;
    use futures::future;
    use rrpc::message::Message;
    use tokio_core::reactor::Core;

    use heartbeater;

    pub fn ping(addr: &SocketAddr, handle: &Handle, mut core: Core) {
        let handle = handle.clone();
        let h2 = handle.clone();
        let beat = heartbeater::beat();

        let v = beat.for_each(move |v| {
            let tcp = TcpStream::connect(&addr, &handle);
            let h = handle.clone();
            let c = tcp.map(move |sock| {
                    let (sink, _strm) = sock.framed(JsonCodec).split();
                    let tic = future::ok::<Message, io::Error>(v)
                        .into_stream()
                        .forward(sink)
                        .then(|ret| {
                                  if let Err(e) = ret {
                                      panic!("failed to write to socket: {}", e)
                                  }
                                  Ok(())
                              });
                    h.spawn(tic);
                })
                .map_err(|_| panic!());

            h2.spawn(c);
            Ok(())
        });

        core.run(v).unwrap();
    }
}

mod heartbeater {
    use std::io;
    use std::time::*;

    use tokio_timer::Timer;
    use futures::Stream;
    use rrpc::message::Message;

    pub fn beat() -> Box<Stream<Item = Message, Error = io::Error>> {
        let timer = Timer::default();
        let ticker = timer.interval(Duration::from_millis(1000));

        Box::new(ticker
                     .map(|_| {
                              println!("------------------------beat-------");
                              Message::Ping {
                                  id: 0,
                                  name: "foooo".to_owned(),
                                  from: "heihei".to_owned(),
                              }
                          })
                     .map_err(|e| panic!(e)))
    }

}
