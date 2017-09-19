use std::net::SocketAddr;
use std::time;

pub struct Builder {
    addr: Option<SocketAddr>,
    heartberat_interval_sec: Option<time::Duration>,
}

const DEFAULT_HEARTBEAT_INTERVAL_SEC: u64 = 2;

impl Builder {
    pub fn new() -> Self {
        Builder {
            addr: None,
            heartberat_interval_sec: None,
        }
    }

    pub fn addr(mut self, sock_addr: SocketAddr) -> Self {
        self.addr = Some(sock_addr);
        self
    }

    pub fn heartbeat_interval(mut self, interval: u64) -> Self {
        self.heartberat_interval_sec = Some(time::Duration::from_secs(interval));
        self
    }

    pub fn build(&mut self) -> Config {
        let addr = self.addr.expect("addr is required");
        let hb = self.heartberat_interval_sec
            .unwrap_or(time::Duration::from_secs(DEFAULT_HEARTBEAT_INTERVAL_SEC));

        Config {
            addr: addr,
            heartberat_interval_sec: hb,
        }
    }
}


pub struct Config {
    addr: SocketAddr,
    heartberat_interval_sec: time::Duration,
}

impl Config {
    pub fn builder() -> Builder {
        Builder::new()
    }

    pub fn addr(&self) -> SocketAddr {
        self.addr
    }

    pub fn heartbeat_interval(&self) -> time::Duration {
        self.heartberat_interval_sec
    }
}
