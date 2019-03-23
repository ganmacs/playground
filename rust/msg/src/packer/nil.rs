use crate::code;
use bytes;

pub fn write_nil<T: bytes::BufMut>(buf: &mut T) -> Result<(), String> {

    buf.put_u8(code::NIL);
    Ok(())
}
