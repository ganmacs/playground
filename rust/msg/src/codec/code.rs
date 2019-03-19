pub const NIL: u8 = 0xc0;

pub const FALSE: u8 = 0xc2;
pub const TRUE: u8 = 0xc3;

pub const UINT8: u8 = 0xcc;
pub const UINT16: u8 = 0xcd;
pub const UINT32: u8 = 0xce;
pub const UINT64: u8 = 0xcf;
pub const INT8: u8 = 0xd0;
pub const INT16: u8 = 0xd1;
pub const INT32: u8 = 0xd2;
pub const INT64: u8 = 0xd3;

pub const FIXSTR: u8 = 0xa0;
pub const STR8: u8 = 0xd9;
pub const STR16: u8 = 0xda;
pub const STR32: u8 = 0xdb;

pub const FIXSTR_LIMIT: usize = (2 << 4) - 1;
pub const STR8_LIMIT: usize = (2 << 8) - 1;
pub const STR16_LIMIT: usize = (2 << 16) - 1;
pub const STR32_LIMIT: usize = (2 << 32) - 1;

pub const BIN8: u8 = 0xc4;
pub const BIN16: u8 = 0xc5;
pub const BIN32: u8 = 0xc6;

pub const BIN8_LIMIT: usize = (2 << 8) - 1;
pub const BIN16_LIMIT: usize = (2 << 16) - 1;
pub const BIN32_LIMIT: usize = (2 << 32) - 1;

pub const FIXARRAY: u8 = 0x90;
pub const ARRAY16: u8 = 0xdc;
pub const ARRAY32: u8 = 0xdd;

pub const FIXARRAY_LIMIT: usize = (2 << 4) - 1;
pub const ARRAY16_LIMIT: usize = (2 << 16) - 1;
pub const ARRAY32_LIMIT: usize = (2 << 32) - 1;
