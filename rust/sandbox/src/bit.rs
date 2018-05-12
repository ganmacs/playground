pub fn main() {
    merge(1, 255);
}

fn merge(i: u64, i2: u8) -> u64 {
    println!("{:010b}", i);
    println!("{:010b}", i << 8);
    let v = i << 8 | i2 as u64;
    println!("{:010b}", v);
    println!("{:010b}", v & 0xff);
    println!("{:010b}", i2);

    i
}
