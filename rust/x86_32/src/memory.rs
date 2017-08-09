use std::panic;
use errors::Error;
use std::io::{BufReader, Read};

pub struct Memory {
    memory: Vec<u8>,
}

pub const MEMORY_SIZE: usize = 1024 * 1024;
pub const INITIAL_INDEX: usize = 0x7c00;

impl Memory {
    pub fn load<R: Read>(reader: &mut BufReader<R>) -> Memory {
        let mut binary = [0; MEMORY_SIZE + INITIAL_INDEX];
        reader.read(&mut binary[INITIAL_INDEX..]).unwrap();
        Memory::new(binary.to_vec())
    }

    pub fn new(m: Vec<u8>) -> Memory {
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

    pub fn get_i32(&self, i: usize) -> Result<i32, Error> {
        self.get_u32(i).map(|v| v as i32)
    }

    pub fn set_u8(&mut self, i: usize, v: u32) {
        self.memory[i] = (v & 0xFF) as u8;
    }

    pub fn set_u32(&mut self, addr: usize, v: u32) {
        for i in 0..4 {
            self.set_u8(addr + i, v >> (8 * i));
        }
    }
}
