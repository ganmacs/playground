use crate::value::{integer, Value};
use bytes;

pub trait Packer {
    fn pack_bool(self, v: bool) -> Result<(), String>;
    fn pack_nil(self) -> Result<(), String>;
    fn pack_u64(self, v: u64) -> Result<(), String>;
    fn pack_i64(self, v: i64) -> Result<(), String>;
    fn pack_f64(self, v: f64) -> Result<(), String>;
    fn pack_f32(self, v: f32) -> Result<(), String>;
    fn pack_bin(self, v: &[u8]) -> Result<(), String>;
    fn pack_str(self, v: &str) -> Result<(), String>;
    fn pack_ary(self, v: &[Value]) -> Result<(), String>;
}

pub trait Pack {
    fn pack_to<T>(&self, packer: T) -> Result<(), String>
    where
        T: Packer;
}

pub struct BufPacker<T> {
    inner: T,
}

pub fn new() -> BufPacker<bytes::BytesMut> {
    BufPacker {
        inner: bytes::BytesMut::with_capacity(64),
    }
}

pub fn new_from<T: bytes::BufMut>(buf: T) -> BufPacker<T> {
    BufPacker { inner: buf }
}

use crate::packer;

impl<'a, T: bytes::BufMut> Packer for &'a mut BufPacker<T> {
    fn pack_bool(self, v: bool) -> Result<(), String> {
        packer::write_bool(v, &mut self.inner)
    }

    fn pack_nil(self) -> Result<(), String> {
        packer::write_nil(&mut self.inner)
    }

    fn pack_u64(self, v: u64) -> Result<(), String> {
        packer::write_opt_u64(v, &mut self.inner)
    }

    fn pack_i64(self, v: i64) -> Result<(), String> {
        unimplemented!()
    }

    fn pack_f64(self, v: f64) -> Result<(), String> {
        unimplemented!()
    }

    fn pack_f32(self, v: f32) -> Result<(), String> {
        unimplemented!()
    }

    fn pack_bin(self, v: &[u8]) -> Result<(), String> {
        packer::write_bin(v, &mut self.inner)
    }

    fn pack_str(self, v: &str) -> Result<(), String> {
        packer::write_str(v, &mut self.inner)
    }

    fn pack_ary(self, v: &[Value]) -> Result<(), String> {
        packer::write_ary_len(v.len(), &mut self.inner)?;
        for i in v {
            write_value(&mut self.inner, i)?;
        }
        Ok(())
    }
}

fn write_value<T>(packer: &mut T, val: &Value) -> Result<(), String>
where
    T: bytes::BufMut,
{
    match val {
        Value::Boolean(v) => packer::write_bool(*v, packer),
        Value::Nil => packer::write_nil(packer),
        Value::Integer(integer::Integer { ref n }) => match n {
            integer::Number::PosInt(ref v) => packer::write_opt_u64(*v, packer),
            integer::Number::NegInt(ref v) => unimplemented!(),
        },
        // Value::Float(ref n) => {
        //     // n.pack_to(packer);
        // }
        Value::Binary(ref v) => packer::write_bin(v, packer),
        Value::String(ref v) => packer::write_str(v, packer),
        Value::Array(ref v) => {
            packer::write_ary_len(v.len(), packer)?;
            for i in v {
                write_value(packer, i)?;
            }
            Ok(())
        }
        _ => unimplemented!(),
    }
}
