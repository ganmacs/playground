use std::thread;

static NTHREADS: i32 = 10;

fn main() {
    // let mut children = vec![];
    let threads = (0..NTHREADS).map(|i| {
        thread::spawn(move || {
            println!("this is rhread number {}", i);
        })
    });

    for t in threads { let _ = t.join(); }
}
