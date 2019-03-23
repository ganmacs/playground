use super::Value;

impl From<bool> for Value {
    fn from(v: bool) -> Self {
        Value::Boolean(v)
    }
}

impl From<Option<Self>> for Value {
    fn from(v: Option<Self>) -> Self {
        if let Some(val) = v {
            Self::from(val)
        } else {
            Value::Nil
        }
    }
}

macro_rules! from_pos_integer {
    ($($ty:ident)*) => {
        $(
            impl From<$ty> for Value {
                fn from(n: $ty) -> Self {
                    Value::Integer(n.into())
                }
            }
        )*
    };
}

from_pos_integer! {u8 u16 u32 u64 usize}

impl From<f64> for Value {
    fn from(v: f64) -> Self {
        Value::Float(v.into())
    }
}

impl From<f32> for Value {
    fn from(v: f32) -> Self {
        Value::Float(v.into())
    }
}

impl<'a> From<&'a [u8]> for Value {
    fn from(v: &'a [u8]) -> Self {
        Value::Binary(v.into())
    }
}

impl From<Vec<u8>> for Value {
    fn from(v: Vec<u8>) -> Self {
        Value::Binary(v.into())
    }
}

impl From<String> for Value {
    fn from(v: String) -> Self {
        Value::String(v)
    }
}

impl<'a> From<&'a str> for Value {
    fn from(v: &str) -> Self {
        Value::String(v.into())
    }
}

impl From<Vec<Value>> for Value {
    fn from(v: Vec<Value>) -> Self {
        Value::Array(v)
    }
}
