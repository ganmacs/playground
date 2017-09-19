pub mod agent;
pub mod config;

mod tcp_server;

use self::config::*;
use self::agent::Agent;

pub trait Handler {
    type Request;

    type Response;

    fn handle(&self, req: Self::Request) -> Self::Response;
}

struct MyHandler {}

impl MyHandler {
    pub fn new() -> Self {
        MyHandler {}
    }
}

impl Handler for MyHandler {
    type Response = String;

    type Request = String;

    fn handle(&self, req: Self::Request) -> Self::Response {
        let ret = req + " is handled at MyHandler";
        ret.to_string()
    }
}

pub fn new_agent(c: Config) {}

pub fn run() {
    let addr1 = "127.0.0.1:8080".parse().unwrap();
    let config = Config::builder()
        .addr(addr1)
        .heartbeat_interval(10)
        .build();

    Agent::start(MyHandler::new(), config);
}
