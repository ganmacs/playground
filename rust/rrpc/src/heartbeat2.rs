use std::io;
use std::time::Duration;
use std::sync::Arc;
use std::net::SocketAddr;

use tokio_timer::Timer;
use futures::{Stream, Future};
use tokio_core::reactor::Handle;

pub struct Ticker {
    timer: Timer,
    interval: Duration,
}

impl Ticker {
    pub fn new(timer: Timer, interval: Duration) -> Ticker {
        Ticker {
            timer: timer,
            interval: interval,
        }
    }

    pub fn start<S, E>(self, service: S, handle_: &Handle)
    where
        S: Service<Request = (), Error = io::Error> + Send + Sync + 'static,
    {
        let handle = handle_.clone();
        let ticker = self.timer.interval(self.interval).map_err(
            |v| error!("{:?}", v),
        );

        let serv = Arc::new(service);
        handle.spawn(ticker.for_each(move |_| {
            let service = serv.clone();
            service.call(());
            Ok(())
        }))
    }
}
trait Service {}

#[derive(Clone)]
pub struct HealthCheckService {
    timeout: Duration,
    peer: SocketAddr,
}

impl HealthCheckService {
    fn call(&self, request: Self::Request) {
        // let conn = TcpStream::connect(addr, &handle);
        // self.timer.timeout(resp, self.timeout)
    }
}


// impl<E> Service for HealthCheckService
// where
//     E: From<TimeoutError<S::Future>>,
// {
//     // type Request = Request;
//     // type Response = Response;
//     // type Error = :Error;

//     // type Future = Timeout<S::Future>;

//     fn call(&self, request: Self::Request) -> Self::Future {
//         let resp = self.upstream.call(request);
//         // self.timer.timeout(resp, self.timeout)
//     }
// }
