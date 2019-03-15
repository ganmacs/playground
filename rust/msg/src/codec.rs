use bytes;
use bytes::BufMut;

const FALSE: u8 = 0xc2;
const TRUE: u8 = 0xc3;

pub trait Codec {
    fn encode_to(&self, buf: &mut bytes::BytesMut);
}

impl Codec for bool {
    fn encode_to(&self, buf: &mut bytes::BytesMut) {
        if *self {
            buf.put_u8(TRUE)
        } else {
            buf.put_u8(FALSE)
        }
    }
}
