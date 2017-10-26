extern crate rrpc;

use rrpc::config::*;
use rrpc::agent::Agent;

fn main() {
    let builder = Config::builder();
    let config = builder
        .addr("127.0.0.1:8080")
        .peers("127.0.0.1:3001")
        .build();

    Agent::run(config)
}