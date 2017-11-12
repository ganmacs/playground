use std::io;
use std::time::Duration;

use tokio_core::reactor::{Core, Handle};
use tokio_timer::Timer;
use tokio_io::AsyncRead;
use tokio_core::net::TcpStream;
use futures::{Stream, Future, Sink, IntoFuture};
use futures::future::err as future_err;
use futures::stream;

use message::Message;
use config::Config;
use codec::JsonCodec;
use atomic_counter::Counter;

pub fn start(mut core: Core, handle: &Handle, config: &Config) -> () {
    let timer = Timer::default();
    let ticker = timer.interval(config.heartbeat_interval()).map_err(|e| {
        error!("{:?}", e)
    });
    let counter = Counter::new(0);

    core.run(ticker.for_each(
        |_| send_heartbeat(handle, config, counter.clone()),
    )).unwrap();
}

fn send_heartbeat(
    handle: &Handle,
    config: &Config,
    counter: Counter,
) -> Box<Future<Item = (), Error = ()>> {

    let timer = Timer::default();
    if let Some(addr) = config.peers().first() {
        let name = config.name().into();
        let handle = handle.clone();
        let conn = TcpStream::connect(addr, &handle);
        let target = addr.to_string();

        let ping_and_ack = move |sock: TcpStream| {
            let (tx, rx) = sock.framed(JsonCodec).split();

            let p = Message::Ping {
                id: counter.up() as u64,
                to: target,
                from: name,
            };

            debug!("ping sending...");
            handle.spawn(send_message(Box::new(tx), p));

            let recive_ack = rx.into_future().then(|v| match v {
                Err((e, _)) => Err(e),
                Ok((Some(o), _)) => Ok(recv_ack(o)),
                Ok((None, _)) => Err(io::Error::new(io::ErrorKind::Other, "no more message")),
            });

            timer.timeout(recive_ack, Duration::from_secs(1)).then(|v| {
                if let Err(e) = v {
                    error!("Timeout reciving ack from {:?}", e);
                    return Err(e);
                }
                Ok(())
            })
        };

        Box::new(conn.and_then(ping_and_ack).then(|v| {
            if let Err(e) = v {
                panic!(e);
            }
            Ok(())
        }))
    } else {
        Box::new(future_err(()))
    }
}

fn send_message(
    tx: Box<Sink<SinkItem = Message, SinkError = io::Error>>,
    message: Message,
) -> Box<Future<Item = (), Error = ()>> {
    Box::new(
        stream::once::<Message, io::Error>(Ok(message))
            .forward(tx)
            .then(|r| match r {
                Err(e) => panic!("failed at sending ping {}", e),
                Ok(_) => {
                    debug!("Sucess seding ping");
                    Ok(())
                }
            }),
    )
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
