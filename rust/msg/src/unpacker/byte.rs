use bytes;

pub fn read_u8<T>(buf: &mut T) -> Result<u8, String>
where
    T: bytes::Buf,
{
    if buf.remaining() < 1 {
        return Err("invalid range".to_owned());
    }
    Ok(buf.get_u8())
}

pub fn read_u16<T>(buf: &mut T) -> Result<u16, String>
where
    T: bytes::Buf,
{
    if buf.remaining() < 2 {
        return Err("invalid range".to_owned());
    }
    Ok(buf.get_u16_be())
}

pub fn read_u32<T>(buf: &mut T) -> Result<u32, String>
where
    T: bytes::Buf,
{
    if buf.remaining() < 4 {
        return Err("invalid range".to_owned());
    }
    Ok(buf.get_u32_be())
}
