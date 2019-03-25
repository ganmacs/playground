use super::byte;
use crate::code;
use bytes;
use std::string;

pub fn read_str<T>(buf: &mut T) -> Result<String, String>
where
    T: bytes::Buf,
{
    let len = match byte::read_u8(buf)? {
        v if (0xa0 <= v && v <= 0xbf) => (v - 0xa0) as usize,
        code::STR8 => byte::read_u8(buf)? as usize,
        code::STR16 => byte::read_u16(buf)? as usize,
        code::STR32 => byte::read_u32(buf)? as usize,
        v => {
            return Err(format!("Expected str but found: {:?}", v));
        }
    };

    if len <= buf.remaining() {
        let mut ret: Vec<u8> = vec![0; len];
        buf.copy_to_slice(&mut ret[..len]);
        string::String::from_utf8(ret).map_err(|v| format!("{:?}", v))
    } else {
        Err(format!("Out of range {:?} < {:?}", buf.remaining(), len,))
    }
}
