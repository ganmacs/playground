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

#[test]
fn read_pos_int() {
    let mut buf = vec![0x02].into_buf();

    assert_eq!(unpacker::read_pos_int(&mut buf).unwrap(), 2);
}

#[test]
fn read_u16() {
    let mut buf = vec![0xcd, 0x00, 0x02].into_buf();
    assert_eq!(unpacker::read_u16(&mut buf).unwrap(), 2);
}

#[test]
fn read_u32() {
    let mut buf = vec![0xce, 0x00, 0x00, 0x00, 0x02].into_buf();
    assert_eq!(unpacker::read_u32(&mut buf).unwrap(), 2);
}

#[test]
fn read_str() {
    let mut buf = vec![0xa2, 0x61, 0x61].into_buf();
    assert_eq!(unpacker::read_str(&mut buf).unwrap(), "aa".to_string());

    let mut buf = vec![0xd9, 0x02, 0x61, 0x61].into_buf();
    assert_eq!(unpacker::read_str(&mut buf).unwrap(), "aa".to_string());

    let mut buf = vec![0xda, 0x00, 0x02, 0x61, 0x61].into_buf();
    assert_eq!(unpacker::read_str(&mut buf).unwrap(), "aa".to_string());

    let mut buf = vec![0xdb, 0x00, 0x00, 0x00, 0x02, 0x61, 0x61].into_buf();
    assert_eq!(unpacker::read_str(&mut buf).unwrap(), "aa".to_string());
}

#[test]
fn read_ary() {
    let mut buf = vec![0x91, 0x91, 0x01].into_buf();

    assert_eq!(unpacker::read_ary_len(&mut buf).unwrap(), 1);
    assert_eq!(unpacker::read_ary_len(&mut buf).unwrap(), 1);
    assert_eq!(unpacker::read_pos_int(&mut buf).unwrap(), 1);
}
