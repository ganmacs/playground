mod codec;
mod msg;

fn main() {
    println!("Hello, world!");
    let mut msg = msg::new();
    msg.encode(&true);
    // msg.encode(1);
}
