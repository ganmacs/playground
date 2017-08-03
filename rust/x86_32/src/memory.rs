use std::panic;
use errors::Error;

pub struct Memory<'a> {
    memory: &'a [u8],
}

impl<'a> Memory<'a> {
    pub fn new(m: &'a [u8]) -> Memory {
        Memory { memory: m }
    }

    pub fn get_u8(&self, i: usize) -> Result<u8, Error> {
        panic::catch_unwind(|| self.memory[i]).map_err(|_| Error::MemoryOutOfRange(i))
    }

    pub fn get_i8(&self, i: usize) -> Result<i8, Error> {
        panic::catch_unwind(|| self.memory[i] as i8).map_err(|_| Error::MemoryOutOfRange(i))
    }

    pub fn get_u32(&self, x: usize) -> Result<u32, Error> {
        let mut ret: u32 = 0;
        for i in 0..4 {
            let v = self.get_u8(i + x)? as u32;
            ret |= v << (8 * i)
        }

        Ok(ret)
    }
}
