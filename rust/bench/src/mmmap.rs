use memmap::*;
use std::io;
use std::io::{Write, BufReader};
use std::fs::File;
use std::io::Seek;
use std::io::Read;

const IDX: usize = 2^32;

pub fn mmain() {
    open_file();
}

fn open_file() {
    let file = File::open("README").expect("failed");
    let f = unsafe { MmapOptions::new().map(&file).expect("memmap failed") };
    let v1 = &f[IDX..IDX+1000];
    let v2 = &f[0..1000];

    let file = File::open("README").expect("failed");
    let mut f2 = BufReader::new(file);
    f2.seek(io::SeekFrom::Start(IDX as u64));
    let mut v12 = [0;1000];
    f2.read_exact(&mut v12);

    f2.seek(io::SeekFrom::Start(0));
    let mut v22 = [0;1000];
    f2.read_exact(&mut v22);

    assert_eq!(v1.to_vec(), v12.to_vec());
    assert_eq!(v2.to_vec(), v22.to_vec());
}

#[cfg(test)]
mod tests {
    use super::*;
    use test::Bencher;

    #[bench]
    fn b1(b: &mut Bencher) {
        b.iter(|| {
            let file = File::open("README").expect("failed");
            let f = unsafe { MmapOptions::new().map(&file).expect("memmap failed") };
            let v1: &[u8] = &f[IDX..IDX+1000];
            let v2 = &f[0..1000];
            assert!(v1.to_vec() != v2.to_vec());
        })
    }

    #[bench]
    fn b2(b: &mut Bencher) {
        b.iter(|| {
            let file = File::open("README").expect("failed");
            let mut f2 = BufReader::new(file);
            f2.seek(io::SeekFrom::Start(IDX as u64));
            let mut v1 = [0;1000];
            f2.read_exact(&mut v1);

            f2.seek(io::SeekFrom::Start(0));
            let mut v2 = [0;1000];
            f2.read_exact(&mut v2);

            assert!(v1.to_vec() != v2.to_vec());
        })
    }
}
