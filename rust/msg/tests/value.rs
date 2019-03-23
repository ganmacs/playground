use msg::value::{integer, Value};

#[test]
fn from_bool() {
    assert_eq!(Value::from(true), Value::Boolean(true))
}

#[test]
fn from_none() {
    assert_eq!(Value::from(None), Value::Nil)
}

#[test]
fn from_u8() {
    assert_eq!(
        Value::from(1 as u8),
        Value::Integer(integer::Integer {
            n: integer::Number::PosInt(1 as u64)
        })
    )
}

#[test]
fn from_u16() {
    assert_eq!(
        Value::from(1 as u16),
        Value::Integer(integer::Integer {
            n: integer::Number::PosInt(1 as u64)
        })
    )
}

#[test]
fn from_u32() {
    assert_eq!(
        Value::from(1 as u32),
        Value::Integer(integer::Integer {
            n: integer::Number::PosInt(1 as u64)
        })
    )
}

#[test]
fn from_u64() {
    assert_eq!(
        Value::from(1 as u32),
        Value::Integer(integer::Integer {
            n: integer::Number::PosInt(1 as u64)
        })
    )
}

#[test]
fn from_usize() {
    assert_eq!(
        Value::from(1 as usize),
        Value::Integer(integer::Integer {
            n: integer::Number::PosInt(1 as u64)
        })
    )
}

#[test]
fn from_u8_slice() {
    let v: &[u8] = "hello".as_bytes();
    assert_eq!(
        Value::from(v),
        Value::Binary(vec![0x68, 0x65, 0x6c, 0x6c, 0x6f])
    )
}

#[test]
fn from_u8_vec() {
    let v: Vec<u8> = "hello".as_bytes().into();
    assert_eq!(
        Value::from(v),
        Value::Binary(vec![0x68, 0x65, 0x6c, 0x6c, 0x6f])
    )
}

#[test]
fn from_string() {
    let v: String = "hello".into();
    assert_eq!(Value::from(v), Value::String("hello".into()))
}

#[test]
fn from_str() {
    let v: &str = "hello";
    assert_eq!(Value::from(v), Value::String("hello".into()))
}
