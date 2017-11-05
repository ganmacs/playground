use std::io;
use std::time::Duration;

use tokio_core::reactor::{Core, Handle};
use tokio_timer::Timer;
use tokio_io::AsyncRead;
use tokio_core::net::TcpStream;
use futures::{Stream, Future};
use futures::future::{ok as future_ok, err as future_err};

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

fn ping(handle: &Handle, config: &Config, counter: Counter) -> Box<Future<Item = (), Error = ()>> {
    if let Some(addr) = config.peers().first() {
        let name = config.name().into();
        let handle = handle.clone();
        let conn = TcpStream::connect(addr, &handle);
        let target = addr.to_string();

        let sending_ping = move |sock: TcpStream| {
            let (tx, rx) = sock.framed(JsonCodec).split();
            let future_message = future_ok::<Message, io::Error>(Message::Ping {
                                                                     id: counter.up() as u64,
                                                                     to: target,
                                                                     from: name,
                                                                 });
            handle.spawn(future_message
                             .into_stream()
                             .forward(tx)
                             .then(|result| {
                                       if let Err(e) = result {
                                           panic!("failed to write to socket: {}", e)
                                       }
                                       Ok(())
                                   }));
            rx
        };

        Box::new(conn.map(sending_ping)
                     .flatten_stream()
                     .into_future()
                     .then(|v| {
                               if let Err(e) = v {
                                   panic!("oh")
                               }
                               Ok(())
                           }))
    } else {
        Box::new(future_err(()))
    }
}
