use super::integer;
use crate::pack;

#[derive(Clone, PartialEq, Debug)]
pub enum Number {
    PosInt(u64),
    NegInt(i64),
}

#[derive(Clone, PartialEq, Debug)]
pub struct Integer {
    pub n: Number,
}

macro_rules! impl_from_pos_integer {
    ($($ty:ty)*) => {
        $(
            impl From<$ty> for Integer {
                #[inline]
                fn from(u: $ty) -> Self {
                    Integer { n: { Number::PosInt(u as u64) } }
                }
            }
        )*
    };
}

impl_from_pos_integer! {u8 u16 u32 u64 usize}

impl pack::Pack for Integer {
    fn pack_to<T>(&self, packer: T) -> Result<(), String>
    where
        T: pack::Packer,
    {
        match self.n {
            integer::Number::PosInt(ref v) => packer.pack_u64(*v),
            integer::Number::NegInt(ref v) => packer.pack_i64(*v),
        }
    }
}
