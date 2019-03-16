mod code;

use bytes;
use bytes::BufMut;

pub trait Codec {
     fn encode_to(&self, buf: &mut bytes::BytesMut);
}

impl Codec for u64 {
    fn encode_to(&self, buf: &mut bytes::BytesMut) {
        buf.put_u8(code::UINT64);
        buf.put_u64_be(*self)
    }
}

impl Codec for u32 {
    fn encode_to(&self, buf: &mut bytes::BytesMut) {
            buf.put_u8(code::UINT32);
            buf.put_u32_be(*self)
    }
}

impl Codec for u16 {
    fn encode_to(&self, buf: &mut bytes::BytesMut) {
            buf.put_u8(code::UINT16);
            buf.put_u16_be(*self)
    }
}

impl Codec for u8 {
    fn encode_to(&self, buf: &mut bytes::BytesMut) {
        buf.put_u8(code::UINT8);
        buf.put_u8(*self);
    }
}

impl Codec for i64 {
    fn encode_to(&self, buf: &mut bytes::BytesMut) {
        buf.put_u8(code::INT64);
        buf.put_i64_be(*self)
    }
}

impl Codec for i32 {
    fn encode_to(&self, buf: &mut bytes::BytesMut) {
            buf.put_u8(code::INT32);
            buf.put_i32_be(*self)
    }
}

impl Codec for i16 {
    fn encode_to(&self, buf: &mut bytes::BytesMut) {
            buf.put_u8(code::INT16);
            buf.put_i16_be(*self)
    }
}

impl Codec for i8 {
    fn encode_to(&self, buf: &mut bytes::BytesMut) {
        buf.put_u8(code::INT8);
        buf.put_i8(*self);
    }
}
impl Codec for bool {
    fn encode_to(&self, buf: &mut bytes::BytesMut) {
        buf.put_u8(if *self {
            code::TRUE
        } else {
            code::FALSE
        })
    }
}
