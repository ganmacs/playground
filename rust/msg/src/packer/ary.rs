use crate::code;
use bytes;

const FIXARRAY_LIMIT: usize = 1 << 4;
const ARRAY16_LIMIT: usize = 1 << 16;
const ARRAY32_LIMIT: usize = 1 << 32;

pub fn write_ary_len<T: bytes::BufMut>(len: usize, buf: &mut T) -> Result<(), String> {
    if len < FIXARRAY_LIMIT {
        buf.put_u8(code::FIXARRAY | (len as u8));
    } else if len < ARRAY16_LIMIT {
        buf.put_u8(code::ARRAY16);
        buf.put_u16_be(len as u16);
    } else if len < ARRAY32_LIMIT {
        buf.put_u8(code::ARRAY32);
        buf.put_u32_be(len as u32);
    } else {
        return Err("out of range".to_owned());
    }
    Ok(())
}
