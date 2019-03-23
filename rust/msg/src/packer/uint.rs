use crate::code;
use bytes;

const POS_INT_LIMIT: usize = 1 << 7;
const UINT8_LIMIT: usize = 1 << 8;
const UINT16_LIMIT: usize = 1 << 16;
const UINT32_LIMIT: usize = 1 << 32;

pub fn write_u8_with_opt<T: bytes::BufMut>(v: u8, buf: &mut T) -> Result<(), String> {
    if (v as usize) < POS_INT_LIMIT {
        buf.put_u8(code::POSINT | v);
        Ok(())
    } else {
        write_u8(v, buf)
    }
}

pub fn write_u8<T: bytes::BufMut>(v: u8, buf: &mut T) -> Result<(), String> {
    buf.put_u8(code::UINT8);
    buf.put_u8(v);
    Ok(())
}

pub fn write_u16<T: bytes::BufMut>(v: u16, buf: &mut T) -> Result<(), String> {
    buf.put_u8(code::UINT16);
    buf.put_u16_be(v);
    Ok(())
}

pub fn write_u32<T: bytes::BufMut>(v: u32, buf: &mut T) -> Result<(), String> {
    buf.put_u8(code::UINT32);
    buf.put_u32_be(v);
    Ok(())
}

pub fn write_u64<T: bytes::BufMut>(v: u64, buf: &mut T) -> Result<(), String> {
    buf.put_u8(code::UINT64);
    buf.put_u64_be(v);
    Ok(())
}

pub fn write_opt_u64<T: bytes::BufMut>(v: u64, buf: &mut T) -> Result<(), String> {
    // TODO: write value directory?
    if v < UINT8_LIMIT as u64 {
        write_u8_with_opt(v as u8, buf)
    } else if v < UINT16_LIMIT as u64 {
        write_u16(v as u16, buf)
    } else if v < UINT32_LIMIT as u64 {
        write_u32(v as u32, buf)
    } else {
        write_u64(v, buf)
    }
}

pub fn write_usize<T: bytes::BufMut>(v: usize, buf: &mut T) -> Result<(), String> {
    if v < UINT8_LIMIT {
        write_u8_with_opt(v as u8, buf)
    } else if v < UINT16_LIMIT {
        write_u16(v as u16, buf)
    } else if v < UINT32_LIMIT {
        write_u32(v as u32, buf)
    } else {
        write_u64(v as u64, buf)
    }
}
