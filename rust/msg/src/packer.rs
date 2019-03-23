pub mod ary;
pub mod bin;
pub mod bool;
pub mod int;
pub mod nil;
pub mod str;
pub mod uint;

pub use self::ary::write_ary_len;
pub use self::bin::write_bin;
pub use self::bool::write_bool;
pub use self::nil::write_nil;
pub use self::str::write_str;
pub use self::uint::write_opt_u64;
// use crate::codec::code;
// use bytes;
