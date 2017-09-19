use rpc::config;
use rpc::Handler;

pub struct Agent<T> {
    config: config::Config,
    handler: T,
}

impl<T> Agent<T> {
    pub fn start(handler: T, config: config::Config) -> Self
        where T: Handler
    {
        Agent::new(handler, config)
    }

    fn new(handler: T, config: config::Config) -> Self {
        Agent {
            config: config,
            handler: handler,
        }
    }
}
