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
    heartbeater::run(ping, core);
}

mod codec_tcp {
    use std::io;
    use std::net::SocketAddr;

    use rrpc::codec::JsonCodec;
    use rrpc::message::Message;

    use futures::{Stream, Future};
    use futures::future;
    use tokio_core::net::TcpStream;
    use tokio_core::reactor::Handle;
    use tokio_io::AsyncRead;

    use std::time::*;
    use tokio_timer::Timer;


    pub fn ping(addr: &SocketAddr,
                handle: &Handle)
                -> Box<Stream<Item = Message, Error = io::Error>> {
        let handle = handle.clone();
        let tcp = TcpStream::connect(&addr, &handle);

        Box::new(tcp.map(move |sock| {
                let ping = Message::Ping {
                    id: 0,
                    name: "foooo".to_owned(),
                    from: "heihei".to_owned(),
                };

                let timer = Timer::default();
                let ticker = timer.interval(Duration::from_millis(1000));

                let (sink, strm) = sock.framed(JsonCodec).split();


                handle.spawn(future::ok::<Message, io::Error>(ping)
                                 .into_stream()
                                 .forward(sink)
                                 .then(|result| {
                                           if let Err(e) = result {
                                               panic!("failed to write to socket: {}", e)
                                           }
                                           Ok(())
                                       }));

                strm
            })
                     .flatten_stream())
    }
}

mod heartbeater {
    use std::io;
    use std::time::*;

    use tokio_core::reactor::Core;
    use tokio_timer::Timer;
    // use tokio_core::reactor::Handle;
    use futures::{Stream, Future};
    use rrpc::message::Message;

    // T need codec?
    pub fn run(mut conn: Box<Stream<Item = Message, Error = io::Error>>, mut core: Core) -> () {
        let timer = Timer::default();
        let ticker = timer.interval(Duration::from_millis(1000));

        let v = ticker
            .for_each(move |_| {
                          println!("-------------------------------");
                          conn.poll();
                          // println!("{:?}", "saioku");
                          Ok(())
                      })
            .map_err(|e| panic!(e));

        core.run(v).unwrap();
    }
}

// let heartbeater = ticker.for_each(move |_| {
//     let stream = TcpStream::connect(&addr, &handle);
//     let request = stream.map(|sock| {
//         let (sink, stream) = sock.framed(JsonCodec).split();

//         // sink.
//         // println!("write from client");
//         // JSonCodec
//         // tokio_io::io::write_all(sock, b"this is a client")
//         stream
//     });

//     let a = request
//         .and_then(|stream)| {
//             out.write_all()
//             // println!("waitng from server");
//             // tokio_io::io::read_to_end(sock, Vec::new())
//         })
//                                   .map_err(|e| panic!("error {:?}", e))
//                                   .map(|e| println!("success {:?}", e));

//                                   handle.spawn(a);
//                                   Ok(())
// });
// .for_each(|_| Ok(()));
// let heartbeater = heartbeat::connect(&addr, &handle);
// let mut out = io::stdout();
// core.run(heartbeater.for_each(|v| out.write_all(&v)))
//     .unwrap();
