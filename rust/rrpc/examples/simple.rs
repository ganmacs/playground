extern crate rrpc;
extern crate env_logger;

use rrpc::config::*;
use rrpc::agent::Agent;

fn main() {
    env_logger::init_from_env("RRPC_LOG_LEVEL");

    let builder = Config::builder();
    let config = builder
        .name("awesome server")
        .addr("127.0.0.1:8080")
        .peers("127.0.0.1:8081")
        .build();

    Agent::run(config)
}
