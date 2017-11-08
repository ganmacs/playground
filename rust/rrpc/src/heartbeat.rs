use std::io;
use std::time::Duration;

use tokio_core::reactor::{Core, Handle};
use tokio_timer::Timer;
use tokio_io::AsyncRead;
use tokio_core::net::TcpStream;
use futures::{Stream, Future};
use futures::future::err as future_err;
use futures::stream;

use message::Message;
use config::Config;
use codec::JsonCodec;
use atomic_counter::Counter;

pub fn start(mut core: Core, handle: &Handle, config: &Config) -> () {
    let timer = Timer::default();
    let ticker = timer.interval(config.heartbeat_interval());
    let counter = Counter::new(0);
    core.run(ticker.map_err(|_| panic!()).for_each(|_| {
        ping(&handle, &config, counter.clone())
    })).unwrap();
}

fn ping(handle: &Handle, config: &Config, counter: Counter) -> Box<Future<Item = (), Error = ()>> {
    let timer = Timer::default();
    if let Some(addr) = config.peers().first() {
        let name = config.name().into();
        let handle = handle.clone();
        let conn = TcpStream::connect(addr, &handle);
        let target = addr.to_string();

        let ping_and_ack = move |sock: TcpStream| {
            let (tx, rx) = sock.framed(JsonCodec).split();
            let pping = stream::once::<Message, io::Error>(Ok(Message::Ping {
                id: counter.up() as u64,
                to: target,
                from: name,
            })).forward(tx)
                .then(|r| match r {
                    Err(e) => panic!("failed at sending ping {}", e),
                    Ok(_) => {
                        debug!("Sucess seding ping");
                        Ok(())
                    }
                });
            debug!("ping sending...");
            handle.spawn(pping);

            let recive_ack = rx.map(|m| Ok(recv_ack(m))).into_future().then(|v| {
                if let Err((e, _)) = v {
                    e
                }
                Ok(())
            });

            timer.timeout(recive_ack, Duration::from_secs(1)).then(|v| {
                if let Err(e) = v {
                    println!("{:?}", e.hoge());
                    error!("Timeout reciving ack from");
                }
                Ok(())
            })
        };

        Box::new(conn.and_then(ping_and_ack).then(|v| {
            if let Err(e) = v {
                panic!("oh 3")
            }
            Ok(())
        }))
    } else {
        Box::new(future_err(()))
    }
}


fn recv_ack(ping: Message) {
    match ping {
        Message::Ping { id, from, .. } => {
            error!("[PING:{:?}] unexpected message: from {:?}", id, from);
            panic!("whats")
        }
        Message::Ack { id, from, .. } => info!("[ACK:{:?}] from {:?} ", id, from),
    }
}
