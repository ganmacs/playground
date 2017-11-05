extern crate rrpc;

use rrpc::config::*;
use rrpc::agent::Agent;

fn main() {
    let builder = Config::builder();
    let config = builder
        .name("awesome server")
        .addr("127.0.0.1:8080")
        .peers("127.0.0.1:8081")
        .build();

    Agent::run(config)
}
