use super::byte;
use crate::code;
use bytes;

pub fn read_u8<T>(buf: &mut T) -> Result<u8, String>
where
    T: bytes::Buf,
{
    match byte::read_u8(buf)? {
        code::UINT8 => byte::read_u8(buf),
        v => Err(format!("Expected u8 but found: {:?}", v)),
    }
}

pub fn read_pos_int<T>(buf: &mut T) -> Result<u8, String>
where
    T: bytes::Buf,
{
    let v = byte::read_u8(buf)?;
    if v < 128 {
        Ok(v)
    } else {
        Err(format!("Expected pos int but found: {:?}", v))
    }
}

pub fn read_u16<T>(buf: &mut T) -> Result<u16, String>
where
    T: bytes::Buf,
{
    match byte::read_u8(buf)? {
        code::UINT16 => byte::read_u16(buf),
        v => Err(format!("Expected u16 but found: {:?}", v)),
    }
}

pub fn read_u32<T>(buf: &mut T) -> Result<u32, String>
where
    T: bytes::Buf,
{
    match byte::read_u8(buf)? {
        code::UINT32 => byte::read_u32(buf),
        v => Err(format!("Expected u32 but found: {:?}", v)),
    }
}
