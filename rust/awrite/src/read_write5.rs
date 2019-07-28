use std::sync::mpsc;
use std::thread;

pub fn run() {
    let (sender, receiver) = mpsc::channel();
    let sender2 = sender.clone();

    thread::spawn(move || {
        sender.send(1).unwrap();
    });

    thread::spawn(move || {
        sender2.send(2).unwrap();
    });

    let msg = receiver.recv().unwrap();
    let msg2 = receiver.recv().unwrap();

    println!("{:?}", msg);
    println!("{:?}", msg2);
}
