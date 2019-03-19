mod code;

use bytes;

pub trait Codec<T> {
    fn encode_to(&self, buf: &mut T);
}

impl<T: bytes::BufMut> Codec<T> for &str {
    fn encode_to(&self, buf: &mut T) {
        let len = self.len();
        if len <= code::FIXSTR_LIMIT {
            buf.put_u8(code::FIXSTR | len as u8);
            buf.put_slice(self.as_bytes());
        } else if len <= code::STR8_LIMIT {
            buf.put_u8(code::STR8);
            buf.put_u8(len as u8);
            buf.put_slice(self.as_bytes());
        } else if len <= code::STR16_LIMIT {
            buf.put_u8(code::STR16);
            buf.put_u16_be(len as u16);
            buf.put_slice(self.as_bytes());
        } else if len <= code::STR32_LIMIT {
            buf.put_u8(code::STR32);
            buf.put_u32_be(len as u32);
            buf.put_slice(self.as_bytes());
        } else {
            unreachable!();
        }
    }
}
impl<T: bytes::BufMut, U: Codec<T>> Codec<T> for Vec<U> {
    fn encode_to(&self, buf: &mut T) {
        let len = self.len();
        if len <= code::FIXARRAY_LIMIT {
            buf.put_u8(code::FIXARRAY | len as u8);
        } else if len <= code::ARRAY16_LIMIT {
            buf.put_u8(code::ARRAY16);
            buf.put_u16_be(len as u16);
        } else if len <= code::ARRAY32_LIMIT {
            buf.put_u8(code::ARRAY32);
            buf.put_u32_be(len as u32);
        } else {
            unreachable!();
        }

        for item in self {
            item.encode_to(buf);
        }
    }
}

impl<T: bytes::BufMut> Codec<T> for [u8] {
    fn encode_to(&self, buf: &mut T) {
        let len = self.len();
        if len <= code::BIN8_LIMIT {
            buf.put_u8(code::BIN8);
            buf.put(self)
        } else if len <= code::BIN16_LIMIT {
            buf.put_u8(code::BIN16);
            buf.put(self)
        } else if len <= code::BIN32_LIMIT {
            buf.put_u8(code::BIN32);
            buf.put(self)
        } else {
            unreachable!(); // should it return Err?
        }
    }
}

impl<T: bytes::BufMut> Codec<T> for u64 {
    fn encode_to(&self, buf: &mut T) {
        buf.put_u8(code::UINT64);
        buf.put_u64_be(*self)
    }
}

impl<T: bytes::BufMut> Codec<T> for u32 {
    fn encode_to(&self, buf: &mut T) {
        buf.put_u8(code::UINT32);
        buf.put_u32_be(*self)
    }
}

impl<T: bytes::BufMut> Codec<T> for u16 {
    fn encode_to(&self, buf: &mut T) {
        buf.put_u8(code::UINT16);
        buf.put_u16_be(*self)
    }
}

impl<T: bytes::BufMut> Codec<T> for u8 {
    fn encode_to(&self, buf: &mut T) {
        buf.put_u8(code::UINT8);
        buf.put_u8(*self);
    }
}

impl<T: bytes::BufMut> Codec<T> for i64 {
    fn encode_to(&self, buf: &mut T) {
        buf.put_u8(code::INT64);
        buf.put_i64_be(*self)
    }
}

impl<T: bytes::BufMut> Codec<T> for i32 {
    fn encode_to(&self, buf: &mut T) {
        buf.put_u8(code::INT32);
        buf.put_i32_be(*self)
    }
}

impl<T: bytes::BufMut> Codec<T> for i16 {
    fn encode_to(&self, buf: &mut T) {
        buf.put_u8(code::INT16);
        buf.put_i16_be(*self)
    }
}

impl<T: bytes::BufMut> Codec<T> for i8 {
    fn encode_to(&self, buf: &mut T) {
        buf.put_u8(code::INT8);
        buf.put_i8(*self);
    }
}

impl<T: bytes::BufMut> Codec<T> for bool {
    fn encode_to(&self, buf: &mut T) {
        buf.put_u8(if *self { code::TRUE } else { code::FALSE })
    }
}
