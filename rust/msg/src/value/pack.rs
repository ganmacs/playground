use super::Value;
use crate::pack;

impl pack::Pack for Value {
    fn pack_to<T>(&self, packer: T) -> Result<(), String>
    where
        T: pack::Packer,
    {
        match *self {
            Value::Boolean(v) => packer.pack_bool(v),
            Value::Nil => packer.pack_nil(),
            Value::Integer(ref n) => n.pack_to(packer),
            Value::Float(ref n) => n.pack_to(packer),
            Value::Binary(ref v) => packer.pack_bin(v),
            Value::String(ref v) => packer.pack_str(v),
            Value::Array(ref v) => packer.pack_ary(v),
            _ => unimplemented!(),
        }
    }
}
