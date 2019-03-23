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
