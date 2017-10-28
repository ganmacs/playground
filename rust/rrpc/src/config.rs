use std::net::{SocketAddr, ToSocketAddrs};
use std::time;

pub struct Builder {
    name: Option<String>,
    addr: Option<SocketAddr>,
    peers: Option<Vec<SocketAddr>>,
    heartberat_interval_sec: Option<time::Duration>,
}

const DEFAULT_HEARTBEAT_INTERVAL_SEC: u64 = 2;

impl Builder {
    pub fn new() -> Self {
        Builder {
            name: None,
            addr: None,
            peers: None,
            heartberat_interval_sec: None,
        }
    }

    pub fn name<T: Into<String>>(mut self, name: T) -> Self {
        self.name = Some(name.into());
        self
    }

    pub fn addr<'a>(mut self, sock_addr: &'a str) -> Self {
        let addr = sock_addr.parse().unwrap();
        self.addr = Some(addr);
        self
    }

    pub fn peers<A: ToSocketAddrs>(mut self, addrs: A) -> Self {
        let k = addrs
            .to_socket_addrs()
            .map(|v| v.collect::<Vec<_>>())
            .unwrap();

        self.peers = Some(k);
        self
    }

    pub fn heartbeat_interval(mut self, interval: u64) -> Self {
        self.heartberat_interval_sec = Some(time::Duration::from_secs(interval));
        self
    }

    pub fn build(self) -> Config {
        let name = self.name.expect("name is required");
        let addr = self.addr.expect("address is required");
        let peers = self.peers.expect("peers are required");
        let hb = self.heartberat_interval_sec
            .unwrap_or(time::Duration::from_secs(DEFAULT_HEARTBEAT_INTERVAL_SEC));

        Config {
            name: name,
            addr: addr,
            peers: Box::new(peers),
            heartberat_interval_sec: hb,
        }
    }
}

pub struct Config {
    name: String,
    addr: SocketAddr,
    peers: Box<Vec<SocketAddr>>,
    heartberat_interval_sec: time::Duration,
}

impl Config {
    pub fn builder() -> Builder {
        Builder::new()
    }

    pub fn name(&self) -> &str {
        &self.name
    }

    pub fn addr(&self) -> SocketAddr {
        self.addr
    }

    pub fn heartbeat_interval(&self) -> time::Duration {
        self.heartberat_interval_sec
    }

    pub fn peers(&self) -> &Vec<SocketAddr> {
        &*self.peers
    }
}
