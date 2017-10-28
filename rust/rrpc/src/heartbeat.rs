use std::io;

use tokio_core::reactor::{Core, Handle};
use tokio_timer::Timer;
use tokio_io::AsyncRead;
use tokio_core::net::TcpStream;
use futures::{Stream, Future};
use futures::future::{FutureResult, ok as future_ok, err as future_err};

use message::Message;
use config::Config;
use codec::JsonCodec;
use atomic_counter::Counter;

pub fn start(mut core: Core, handle: &Handle, config: &Config) -> () {
    let timer = Timer::default();
    let ticker = timer.interval(config.heartbeat_interval());
    let counter = Counter::new(0);
    core.run(ticker
                 .map_err(|_| panic!())
                 .for_each(|_| ping(&handle, &config, counter.clone())))
        .unwrap();
}

fn ping(handle: &Handle, config: &Config, counter: Counter) -> FutureResult<(), io::Error> {
    let name: String = config.name().into();

    if let Some(addr) = config.peers().first() {
        let conn = TcpStream::connect(addr, &handle);
        let target = addr.to_string();

        let sending_ping = move |sock: TcpStream| {
            let peer = sock.framed(JsonCodec);
            let future_message = future_ok::<Message, io::Error>(Message::Ping {
                                                                     id: counter.up() as u64,
                                                                     to: target,
                                                                     from: name,
                                                                 });

            future_message.into_stream().forward(peer).map(|_| ())
        };
        handle.spawn(conn.and_then(sending_ping).map_err(|v| panic!(v)));
        future_ok(())
    } else {
        future_err(io::Error::new(io::ErrorKind::Other, "addr required"))
    }
}
