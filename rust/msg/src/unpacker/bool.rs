use super::byte;
use crate::code;
use bytes;

pub fn read_bool<T>(buf: &mut T) -> Result<bool, String>
where
    T: bytes::Buf,
{
    match byte::read_u8(buf)? {
        code::TRUE => Ok(true),
        code::FALSE => Ok(false),
        v => Err(format!(
            "Expected bool({:?} or {:?}) but found: {:?}",
            code::TRUE,
            code::FALSE,
            v
        )),
    }
}
