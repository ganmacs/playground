use crate::codec;
use bytes;

pub struct Msg {
    inner: bytes::BytesMut,
}

pub fn new() -> Msg {
    Msg {
        inner: bytes::BytesMut::with_capacity(64),
    }
}

impl Msg {
    pub fn encode<T>(&mut self, a: &T) -> Result<String, String>
    where
        T: codec::Codec,
    {
        a.encode_to(&mut self.inner);

        println!("{:?}", self.inner);

        return Err("s".to_owned());
    }
}
