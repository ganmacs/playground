pub mod code;
pub mod codec;
pub mod pack;
pub mod packer;
pub mod unpacker;
pub mod value;

use bytes;

pub struct Msg<T> {
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
        a.pack_to(&mut self.inner);
        return Ok("ok".to_owned());
    }
}
