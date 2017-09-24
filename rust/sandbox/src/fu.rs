use std::{thread, time};
use std::io;
use futures::{Poll, Async, IntoFuture};
use futures::stream::Stream;
use futures::Future;

pub fn main() {
    let k = A::new(10);
    let k1 = &mut k.for_each(move |v| {
                                 println!("from A {:?}", v);
                                 B { inner: C { inner: 100, i: 0 } }
                             });

    k1.poll();

}

struct A {
    inner: u64,
    i: u64,
}

impl A {
    pub fn new(i: u64) -> Self {
        A { inner: i, i: 0 }
    }
}

impl Stream for A {
    type Item = u64;
    type Error = io::Error;

    fn poll(&mut self) -> Poll<Option<Self::Item>, Self::Error> {
        println!("{:?}", "this is in A struct");
        let two_sec = time::Duration::from_secs(2);
        thread::sleep(two_sec);

        self.i += 1;

        if self.i % 2 == 0 {
            Ok(Async::Ready(None))
            // Ok(Async::NotReady)
        } else {
            Ok(Async::Ready(Some(self.inner)))
        }
    }
}

struct C {
    inner: u64,
    i: u8,
}

impl Future for C {
    type Item = ();
    type Error = io::Error;

    fn poll(&mut self) -> Poll<Self::Item, Self::Error> {
        println!("{:?}", self.inner);
        if self.i > 3 {
            Ok(Async::Ready(()))
        } else {
            self.i += 1;
            println!("{:?}", self.i);
            // Ok(Async::NotReady);
            Ok(Async::Ready(()))
        }
    }
}

struct B {
    inner: C,
}

impl IntoFuture for B {
    type Future = C;
    type Item = ();
    type Error = io::Error;

    fn into_future(self) -> Self::Future {
        println!("{:?}", "in B Into Future");
        self.inner
    }
}
