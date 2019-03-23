use msg::pack;
use msg::pack::Packer;
use msg::value::Value;

#[test]
fn pack_bool() {
    let mut buf = vec![];
    let mut packer = pack::new_from(&mut buf);
    packer.pack_bool(true).unwrap();
    packer.pack_bool(false).unwrap();
    assert_eq!(buf, &[0xc3, 0xc2]);
}

#[test]
fn pack_nil() {
    let mut buf = vec![];
    let mut packer = pack::new_from(&mut buf);
    packer.pack_nil().unwrap();
    assert_eq!(buf, &[0xc0]);
}

#[test]
fn pack_64_with_small() {
    let mut buf = vec![];
    let mut packer = pack::new_from(&mut buf);
    let vals = vec![
        1,             // fixint
        (1 << 7) - 1,  // fixint
        1 << 7,        // u8
        (1 << 8) - 1,  // u8
        1 << 8,        // u16
        (1 << 16) - 1, // u16
        1 << 16,       // u32
        (1 << 32) - 1, // u32
    ];

    for v in vals {
        packer.pack_u64(v).unwrap();
    }

    assert_eq!(
        buf,
        &[
            0x01, // 1
            0x7f, // (1 << 7) - 1
            0xcc, 0x80, // 1 << 7
            0xcc, 0xff, // (1 << 8) -1
            0xcd, 0x01, 0x00, // 1 << 8
            0xcd, 0xff, 0xff, // (1 << 16) - 1
            0xce, 0x00, 0x01, 0x00, 0x00, // 1 << 16
            0xce, 0xff, 0xff, 0xff, 0xff, // (1 << 32) - 1
        ]
    );
}

#[test]
fn pack_64_with_large() {
    let mut buf = vec![];
    let mut packer = pack::new_from(&mut buf);
    let vals = vec![
        1 << 32, // u64
        // rust doesn't represent (1<<64) - 1 since (1<<64) exceeds u64
        ((1 << 63) - 1) + (1 << 63), // u64
    ];

    for v in vals {
        packer.pack_u64(v).unwrap();
    }

    assert_eq!(
        buf,
        &[
            // 1 << 32
            0xcf, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
            // ((1 << 63) - 1) + (1 << 63)
            0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        ]
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
    let mut packer = pack::new_from(&mut buf);
    packer.pack_str("hello").unwrap();
    assert_eq!(buf, &[0xa5, 0x68, 0x65, 0x6c, 0x6c, 0x6f]);

    let mut buf = vec![];
    let mut packer = pack::new_from(&mut buf);
    packer.pack_str(&gen_str(31)).unwrap();
    assert_eq!(&buf[0..5], &[0xbf, 0x61, 0x61, 0x61, 0x61]);
}

#[test]
fn pack_str8() {
    let mut buf = vec![];
    let mut packer = pack::new_from(&mut buf);
    packer.pack_str(&gen_str(32)).unwrap();
    assert_eq!(&buf[0..5], &[0xd9, 0x20, 0x61, 0x61, 0x61]);

    let mut buf = vec![];
    let mut packer = pack::new_from(&mut buf);
    packer.pack_str(&gen_str(255)).unwrap();
    assert_eq!(&buf[0..5], &[0xd9, 0xff, 0x61, 0x61, 0x61]);
}

#[test]
fn pack_bin() {
    let mut buf = vec![];
    let mut packer = pack::new_from(&mut buf);
    packer.pack_bin(gen_str(255).as_bytes()).unwrap();
    assert_eq!(&buf[0..5], &[0xc4, 0xff, 0x61, 0x61, 0x61]);

    let mut buf = vec![];
    let mut packer = pack::new_from(&mut buf);
    packer.pack_bin(gen_str(256).as_bytes()).unwrap();
    assert_eq!(&buf[0..5], &[0xc5, 0x01, 0x00, 0x61, 0x61]);
}

#[test]
fn pack_ary() {
    let mut buf = vec![];
    let mut packer = pack::new_from(&mut buf);
    packer
        .pack_ary(vec![Value::from(1 as u8), Value::from(1 as u8)].as_ref())
        .unwrap();
    assert_eq!(buf, &[0x92, 0x01, 0x01]);
}

#[test]
fn pack_ary_in_ary() {
    let mut buf = vec![];
    let mut packer = pack::new_from(&mut buf);
    let v = vec![
        Value::from(1 as u8),
        Value::from(vec![Value::from(1 as u8), Value::from(1 as u8)]),
    ];
    packer.pack_ary(&v).unwrap();
    assert_eq!(buf, &[0x92, 0x01, 0x92, 0x01, 0x01]);
}
