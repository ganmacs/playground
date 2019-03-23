use crate::code;
use bytes;

pub const POS_INT_LIMIT: usize = 1 << 7;
pub const INT8_LIMIT: usize = 1 << 8;
pub const INT16_LIMIT: usize = 1 << 16;
pub const INT32_LIMIT: usize = 1 << 32;

pub fn write_i8_with_opt<T: bytes::BufMut>(v: i8, buf: &mut T) -> Result<(), String> {
    if -32 <= v && v < 0 {
        buf.put_u8(code::NEGINT | v as u8);
        Ok(())
    } else {
        write_i8(v, buf)
    }
}

pub fn write_i8<T: bytes::BufMut>(v: i8, buf: &mut T) -> Result<(), String> {
    buf.put_u8(code::INT8);
    buf.put_i8(v);
    Ok(())
}

pub fn write_i16<T: bytes::BufMut>(v: i16, buf: &mut T) -> Result<(), String> {
    buf.put_u8(code::INT16);
    buf.put_i16_be(v);
    Ok(())
}

pub fn write_i32<T: bytes::BufMut>(v: i32, buf: &mut T) -> Result<(), String> {
    buf.put_u8(code::INT32);
    buf.put_i32_be(v);
    Ok(())
}

pub fn write_i64<T: bytes::BufMut>(v: i64, buf: &mut T) -> Result<(), String> {
    buf.put_u8(code::INT64);
    buf.put_i64_be(v);
    Ok(())
}

// pub fn write_isize<T: bytes::BufMut>(v: usize, buf: &mut T) -> Result<(), String> {
