use std::thread;
use std::sync::{Arc, Mutex};

#[derive(Clone, Copy, Debug)]
struct Data {
    a: i32,
}

impl Data {
    pub fn add(&mut self, i: i32) {
        self.a += i
    }
}

pub fn run() {
    t1();
    t2();
    t3();
}

fn t1() {
    let mut children = vec![];
    let mut v = Data { a: 10 };

    for i in 0..10 {
        let th = thread::spawn(move || {
                                   v.a += 1;
                                   println!("{}: {:?}", i, v);
                               });
        children.push(th);
    }

    for child in children {
        let _ = child.join().unwrap();
    }
}

fn t2() {
    let mut children = vec![];
    let v = Arc::new(Mutex::new(Data { a: 10 }));

    for i in 0..10 {
        let d = v.clone();
        let th = thread::spawn(move || {
                                   {
                                       let mut kkk = d.lock().unwrap();
                                       kkk.add(10);
                                   }
                                   println!("{}: {:?}", i, d);
                               });
        children.push(th);
    }

    for child in children {
        let _ = child.join().unwrap();
    }

    println!("{:?}", v);
}

fn t3() {
    use std::sync::mpsc;

    let (tx, rx) = mpsc::channel();

    for i in 0..10 {
        let tx = tx.clone();

        thread::spawn(move || {
                          let answer = i * i;
                          let _ = tx.send(answer);
                      });
    }

    for _ in 0..10 {
        println!("{}", rx.recv().unwrap());
    }
}
