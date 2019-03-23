use crate::code;
use bytes;

const BIN8_LIMIT: usize = 1 << 8;
const BIN16_LIMIT: usize = 1 << 16;
const BIN32_LIMIT: usize = 1 << 32;

pub fn write_bin<T: bytes::BufMut>(v: &[u8], buf: &mut T) -> Result<(), String> {
    let len = v.len();
    if len < BIN8_LIMIT {
        buf.put_u8(code::BIN8);
        buf.put_u8(len as u8);
        buf.put(v)
    } else if len < BIN16_LIMIT {
        buf.put_u8(code::BIN16);
        buf.put_u16_be(len as u16);
        buf.put(v)
    } else if len < BIN32_LIMIT {
        buf.put_u8(code::BIN32);
        buf.put_u32_be(len as u32);
        buf.put(v)
    } else {
        return Err("out of range".to_owned());
    }

    Ok(())
}
