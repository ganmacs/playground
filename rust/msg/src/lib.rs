pub mod codec;

use bytes;

pub struct Msg<T: bytes::BufMut> {
    inner: T,
}

pub fn new() -> Msg<bytes::BytesMut> {
    Msg {
        inner: bytes::BytesMut::with_capacity(64),
    }
}

pub fn new_from<T: bytes::BufMut>(buf: T) -> Msg<T> {
    Msg { inner: buf }
}

impl<T> Msg<T>
where
    T: bytes::BufMut,
{
    pub fn encode<C>(&mut self, a: &C) -> Result<String, String>
    where
        C: codec::Codec<T>,
    {
        a.encode_to(&mut self.inner);
        return Ok("ok".to_owned());
    }
}
