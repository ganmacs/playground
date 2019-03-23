use crate::code;
use bytes;

const FIXSTR_LIMIT: usize = 1 << 5;
const STR8_LIMIT: usize = 1 << 8;
const STR16_LIMIT: usize = 1 << 16;
const STR32_LIMIT: usize = 1 << 32;

pub fn write_str<T: bytes::BufMut>(v: &str, buf: &mut T) -> Result<(), String> {
    let len = v.len();
    if len < FIXSTR_LIMIT {
        buf.put_u8(code::FIXSTR | len as u8);
        buf.put_slice(v.as_bytes());
    } else if len < STR8_LIMIT {
        buf.put_u8(code::STR8);
        buf.put_u8(len as u8);
        buf.put_slice(v.as_bytes());
    } else if len < STR16_LIMIT {
        buf.put_u8(code::STR16);
        buf.put_u16_be(len as u16);
        buf.put_slice(v.as_bytes());
    } else if len < STR32_LIMIT {
        buf.put_u8(code::STR32);
        buf.put_u32_be(len as u32);
        buf.put_slice(v.as_bytes());
    } else {
        return Err("Out of range".to_owned());
    }

    Ok(())
}
