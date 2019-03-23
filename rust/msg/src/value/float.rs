use super::float;
use crate::pack;

#[derive(Clone, PartialEq, Debug)]
pub enum Number {
    Float32(f32),
    Float64(f64),
}

#[derive(Clone, PartialEq, Debug)]
pub struct Float {
    pub n: Number,
}

impl From<f64> for Float {
    #[inline]
    fn from(u: f64) -> Self {
        Float {
            n: { Number::Float64(u) },
        }
    }
}

impl From<f32> for Float {
    #[inline]
    fn from(u: f32) -> Self {
        Float {
            n: { Number::Float32(u) },
        }
    }
}

impl pack::Pack for Float {
    fn pack_to<T>(&self, packer: T) -> Result<(), String>
    where
        T: pack::Packer,
    {
        match self.n {
            float::Number::Float32(ref v) => packer.pack_f32(*v),
            float::Number::Float64(ref v) => packer.pack_f64(*v),
        }
    }
}
