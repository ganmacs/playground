use futures::{Future, Stream, Sink};
use tokio_core::reactor::Core;
use tokio_core::net::TcpListener;
use tokio_io::AsyncRead;

use config::Config;
use codec::JsonCodec;
use message::Message;

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
    let name = config.name().to_string();

    let socket = TcpListener::bind(&config.addr(), &handle).unwrap();
    let listener = socket.incoming().for_each(move |(socket, _addr)| {
        let (tx, rx) = socket.framed(JsonCodec).split();

        // XXX
        let name = name.clone();

        // TODO: 1 is ok?
        let rev = rx.take(1).map(move |m| ping_ack(m, &name));
        let sending = tx.send_all(rev).then(|e| if let Ok(_) = e {
            println!("yoshi");
            Ok(())
        } else {
            println!("{:?}", "yoshijanai");
            Err(())
        });
        handle.spawn(sending);
        Ok(())
    });

    let _ = core.run(listener);
}


fn ping_ack(ping: Message, name: &str) -> Message {
    match ping {
        Message::Ping { id, from, .. } => {
            Message::Ack {
                id: id,
                to: from,
                from: name.into(),
            }
        }
        Message::Ack { .. } => unimplemented!(),
    }
}
