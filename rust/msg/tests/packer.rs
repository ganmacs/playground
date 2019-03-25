use msg::packer;

#[test]
fn write_bool() {
    let mut buf = vec![];
    packer::write_bool(true, &mut buf).unwrap();
    packer::write_bool(false, &mut buf).unwrap();
    assert_eq!(buf, &[0xc3, 0xc2]);
}

#[test]
fn write_u8() {
    let mut buf = vec![];
    packer::write_u8(1, &mut buf).unwrap();
    packer::write_u8(255, &mut buf).unwrap();
    assert_eq!(buf, &[0xcc, 0x01, 0xcc, 0xff]);
}

#[test]
fn write_u16() {
    let mut buf = vec![];
    packer::write_u16(1 << 8, &mut buf).unwrap();
    let v = (1 << 16) - 1;
    packer::write_u16(v as u16, &mut buf).unwrap();
    assert_eq!(buf, &[0xcd, 0x01, 0x00, 0xcd, 0xff, 0xff]);
}

#[test]
fn write_u32() {
    let mut buf = vec![];
    packer::write_u32(1 << 16, &mut buf).unwrap();
    let v: u64 = (1 << 32) - 1;
    packer::write_u32(v as u32, &mut buf).unwrap();
    assert_eq!(
        buf,
        &[0xce, 0x00, 0x01, 0x00, 0x00, 0xce, 0xff, 0xff, 0xff, 0xff]
    );
}

fn gen_str(len: usize) -> String {
    let mut a = String::new();
    for _ in 0..len {
        a += "a";
    }
    a
}

#[test]
fn pack_fixstr() {
    let mut buf = vec![];
    packer::write_str("hello", &mut buf).unwrap();
    assert_eq!(buf, &[0xa5, 0x68, 0x65, 0x6c, 0x6c, 0x6f]);

    let mut buf = vec![];
    packer::write_str(&gen_str(31), &mut buf).unwrap();
    assert_eq!(&buf[0..5], &[0xbf, 0x61, 0x61, 0x61, 0x61]);
}

#[test]
fn write_str8() {
    let mut buf = vec![];
    packer::write_str(&gen_str(32), &mut buf).unwrap();
    assert_eq!(&buf[0..5], &[0xd9, 0x20, 0x61, 0x61, 0x61]);

    let mut buf = vec![];
    packer::write_str(&gen_str(255), &mut buf).unwrap();
    assert_eq!(&buf[0..5], &[0xd9, 0xff, 0x61, 0x61, 0x61]);
}

// #[test]
// fn decode_from_signed_int() {
//     let mut buf = vec![];
//     (-1 as i64).encode_to(&mut buf);
//     (-1 as i32).encode_to(&mut buf);
//     (-1 as i16).encode_to(&mut buf);
//     (-1 as i8).encode_to(&mut buf);
//     assert_eq!(
//         buf,
//         &[
//             0xd3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd2, 0xff, 0xff, 0xff, 0xff,
//             0xd1, 0xff, 0xff, 0xd0, 0xff
//         ]
//     );
// }

// #[test]
// fn decode_from_unsigned_int() {
//     let mut buf = vec![];
//     (1 as u64).encode_to(&mut buf);
//     (1 as u32).encode_to(&mut buf);
//     (1 as u16).encode_to(&mut buf);
//     (1 as u8).encode_to(&mut buf);
//     assert_eq!(
//         buf,
//         &[
//             0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xce, 0x00, 0x00, 0x00, 0x01,
//             0xcd, 0x00, 0x01, 0xcc, 0x01
//         ]
//     );
// }

// #[test]
// fn decode_from_bin() {
//     let mut buf = vec![];
//     let msg1: &[u8] = "le message".as_bytes();
//     msg1.encode_to(&mut buf);
//     assert_eq!(
//         buf,
//         &[0xc4, 0x6c, 0x65, 0x20, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65]
//     );
// }

// #[test]
// fn decode_from_fixarray() {
//     let mut buf = vec![];
//     vec![9 as i32, 42, -9].encode_to(&mut buf);
//     assert_eq!(buf, &[0x93, 0x00, 0x2a, 0xf7]);
// }
