mod bool;
mod byte;
mod uint;

// pub trait UnPack {
//     fn unpack<T>(&self, packer: T) -> Result<(), String>
//     where
//         T: Packer;
// }

pub use self::bool::read_bool;
pub use self::uint::{read_pos_int, read_u8};
