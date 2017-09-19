pub mod server;
pub mod client;

use env_logger;
use std::{thread, time};

pub fn run() {
    let _ = env_logger::init();

    let c = thread::spawn(move || {
                              let s = server::Server::new("127.0.0.1:8080");
                              s.start();
                          });

    let ten_millis = time::Duration::from_millis(1000);
    thread::sleep(ten_millis);

    let c1 = thread::spawn(move || client::Client::new("127.0.0.1:8080").exec("this is 1"));
    let c2 = thread::spawn(move || client::Client::new("127.0.0.1:8080").exec("this is 2"));
    let c3 = thread::spawn(move || client::Client::new("127.0.0.1:8080").exec("this is 3"));

    let _ = c1.join();
    let _ = c2.join();
    let _ = c3.join();
}
