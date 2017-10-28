extern crate rrpc;
extern crate tokio_core;

use tokio_core::reactor::Core;

use rrpc::config::*;
use rrpc::heartbeat;

pub fn main() {
    let core = Core::new().unwrap();
    let handle = core.handle();

    let builder = Config::builder();
    let config = builder
        .name("awesome client")
        .addr("127.0.0.1:8081")
        .peers("127.0.0.1:8080")
        .build();

    heartbeat::start(core, &handle, &config);
}
