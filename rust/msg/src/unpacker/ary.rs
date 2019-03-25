use super::byte;
use crate::code;
use bytes;

pub fn read_ary_len<T>(buf: &mut T) -> Result<usize, String>
where
    T: bytes::Buf,
{
    let len = match byte::read_u8(buf)? {
        v if (0x90 <= v && v <= 0x9f) => (v - 0x90) as usize,
        code::ARRAY16 => byte::read_u16(buf)? as usize,
        code::ARRAY32 => byte::read_u32(buf)? as usize,
        v => {
            return Err(format!("Expected str but found: {:?}", v));
        }
    };

    Ok(len)
}
