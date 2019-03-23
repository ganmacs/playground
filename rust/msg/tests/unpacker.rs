use bytes::IntoBuf;
use msg::unpacker;

#[test]
fn read_bool() {
    let mut buf = vec![0xc3, 0xc2].into_buf();

    assert_eq!(unpacker::read_bool(&mut buf).unwrap(), true);
    assert_eq!(unpacker::read_bool(&mut buf).unwrap(), false);
}

#[test]
fn read_u8() {
    let mut buf = vec![0xcc, 0x02].into_buf();

    assert_eq!(unpacker::read_u8(&mut buf).unwrap(), 2);
}
