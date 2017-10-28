use std::io;

use tokio_core::reactor::{Core, Handle};
use tokio_timer::Timer;
use tokio_io::AsyncRead;
use tokio_core::net::TcpStream;
use futures::{Stream, Future, future};

use message::Message;
use config::Config;
use codec::JsonCodec;

pub fn start(mut core: Core, handle: &Handle, config: &Config) -> () {
    let timer = Timer::default();
    let ticker = timer.interval(config.heartbeat_interval());
    core.run(ticker
                 .map_err(|_| panic!())
                 .for_each(|_| {
                               ping(&handle, &config);
                               Ok(())
                           }))
        .unwrap();

}

// Box<futures::Stream<Item=(), Error=std::io::Error>>
fn ping(handle: &Handle, config: &Config) {
    if let Some(addr) = config.peers().first() {
        let conn = TcpStream::connect(addr, &handle);

        let c = conn.and_then(move |sock| {
                let peer = sock.framed(JsonCodec);
                let future_message = future::ok::<Message, io::Error>(Message::Ping {
                                                                          id: 0,
                                                                          name: "a".to_string(),
                                                                          from: "b".to_string(),
                                                                      });

                future_message.into_stream().forward(peer).map(|_| ())
            })
            .map_err(|v| panic!(v));
        handle.spawn(c);
    } else {
        panic!("addr required")
    }
}
