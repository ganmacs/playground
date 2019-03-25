mod ary;
mod bool;
mod byte;
mod str;
mod uint;

// pub trait UnPack {
//     fn unpack<T>(&self, packer: T) -> Result<(), String>
//     where
//         T: Packer;
// }

pub use self::ary::read_ary_len;
pub use self::bool::read_bool;
pub use self::str::read_str;
pub use self::uint::{read_pos_int, read_u16, read_u32, read_u8};
