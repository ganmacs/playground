extern crate bench;

use bench::*;

fn main() {
    bench::mmain();

    // let mut v = Vec::from(bench::seed());
    // bench::vector_get32(&mut v);

    // let mut v = bench::Slice::from(&bench::seed());
    // bench::slice_get32(&mut v);

    // let mut v = bench::BytesMut::from(bench::seed());
    // bench::bytes_get32(&mut v);
}
