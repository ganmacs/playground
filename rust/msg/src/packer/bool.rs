use crate::code;
use bytes;

pub fn write_bool<T: bytes::BufMut>(v: bool, buf: &mut T) -> Result<(), String> {
    buf.put_u8(if v { code::TRUE } else { code::FALSE });
    Ok(())
}
