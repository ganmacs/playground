// use errors::Error;
use memory::{Memory, INITIAL_INDEX};
use errors::Error;
use register::*;
use instruction;
use std::io::BufReader;
use std::fs::File;

const CARRY_FLAG: u32 = 1;
const ZERO_FLAG: u32 = (1 << 6);
const SIGN_FLAG: u32 = (1 << 7);
const OVERFLOW_FLAG: u32 = (1 << 11);

pub struct Emulator {
    pub eip: u32,
    memory: Memory,
    register: Register,
    eflags: u32,
}

pub fn run(file_path: String) -> Result<(), Error> {
    let file = File::open(file_path)?;
    let buffer = &mut BufReader::new(file);

    let mem = Memory::load(buffer);
    let emu = &mut Emulator::new(mem, INITIAL_INDEX as u32);
    emu.run()
}


impl Emulator {
    pub fn new(memory: Memory, esp: u32) -> Emulator {
        let mut emu = Emulator {
            memory: memory,
            eip: 0x7c00,
            register: Register::new(),
            eflags: 0,
        };

        emu.register.set(ESP, esp);
        emu
    }

    pub fn run(&mut self) -> Result<(), Error> {
        loop {
            let code = self.get_code8(0)?;
            println!("EIP = {:02X}, Code = {:02X}", self.eip, code);

            self.exec(code)?;
            // self.dump();

            if self.eip == 0x00 {
                println!("end of program");
                break;
            }
        }
        self.dump();
        Ok(())
    }

    pub fn exec(&mut self, op: u8) -> Result<(), Error> {
        match op {
            0x01 => instruction::add_rm32_r32(self),
            0x3B => instruction::cmp_r32_rm32(self),
            0x50...0x57 => instruction::push_r32(self),
            0x58...0x5E => instruction::pop_r32(self),
            0x6A => instruction::push_i8(self),
            0x78 => instruction::js(self),
            0x7E => instruction::jle(self),
            0x83 => instruction::opcode_83(self),
            0x89 => instruction::mov_rm32_r32(self),
            0x8B => instruction::mov_r32_rm32(self),
            0xB8...0xBF => self.mov_r32_imm32(),
            0xC3 => instruction::ret(self),
            0xC7 => instruction::mov_rm32_imm32(self),
            0xC9 => instruction::leave(self),
            0xE8 => instruction::call_rel32(self),
            0xE9 => instruction::jmp_rel32(self),
            0xEB => self.jmp_rel8(),
            0xF7 => instruction::opcode_f7(self),
            0xFF => instruction::code_ff(self),
            _ => Err(Error::UnknownOpcode(op as usize)),
        }
    }


    fn mov_r32_imm32(&mut self) -> Result<(), Error> {
        let reg: u8 = self.get_code8(0)? - 0xB8;
        let value: u32 = self.get_code32(1).unwrap();
        self.register.set(reg as usize, value);
        self.eip += 5;
        Ok(())
    }

    fn jmp_rel8(&mut self) -> Result<(), Error> {
        let rel = self.get_sign_code8(1)?;
        let v = (2 + rel) as i64 + (self.eip as i64); // XXX
        self.eip = v as u32;
        Ok(())
    }

    pub fn dump(&mut self) {
        self.register.dump();
        println!("EIP {:08X}", self.eip);
    }

    fn get_code32(&mut self, i: usize) -> Result<u32, Error> {
        self.memory.get_u32(self.eip as usize + i)
        // eip+=4
    }

    pub fn get_sign_code32(&mut self, i: usize) -> Result<i32, Error> {
        self.get_code32(i).map(|v| v as i32)
        // eip+=4
    }

    fn get_code8(&mut self, i: usize) -> Result<u8, Error> {
        self.memory.get_u8(self.eip as usize + i)
        // eip+=1
    }


    pub fn get_sign_code8(&mut self, i: usize) -> Result<i8, Error> {
        self.memory.get_i8(self.eip as usize + i)
        // eip+=1
    }

    pub fn get_memory32(&mut self, i: usize) -> Result<u32, Error> {
        self.memory.get_u32(i)
    }

    // --------

    pub fn update_eflag_sub(&mut self, v1: u32, v2: u32, v3: u64) {
        self.set_carry_flag((v3 >> 32) == 1);
        self.set_zero_flag(v3 == 0);
        let v1s = v1 >> 31;
        let v2s = v2 >> 31;
        let v3s = (v3 >> 31 & 1) as u32;
        self.set_sign_flag(v3s == 1);
        self.set_overflow_flag(v1s != v2s && v1s != v3s);
    }

    fn set_sign_flag(&mut self, is_negative: bool) {
        if is_negative {
            self.eflags |= SIGN_FLAG;
        } else {
            self.eflags &= !SIGN_FLAG;
        }
    }

    fn set_overflow_flag(&mut self, is_overflow: bool) {
        if is_overflow {
            self.eflags |= OVERFLOW_FLAG;
        } else {
            self.eflags &= !OVERFLOW_FLAG;
        }
    }

    fn set_carry_flag(&mut self, is_carry: bool) {
        if is_carry {
            self.eflags |= CARRY_FLAG;
        } else {
            self.eflags &= !CARRY_FLAG;
        }
    }

    fn set_zero_flag(&mut self, is_zero: bool) {
        if is_zero {
            self.eflags |= ZERO_FLAG;
        } else {
            self.eflags &= !ZERO_FLAG;
        }
    }

    pub fn is_set_zf(&mut self) -> bool {
        (self.eflags & ZERO_FLAG) != 0
    }

    pub fn is_set_cf(&mut self) -> bool {
        (self.eflags & CARRY_FLAG) != 0
    }

    pub fn is_set_sf(&mut self) -> bool {
        (self.eflags & SIGN_FLAG) != 0
    }

    pub fn is_set_of(&mut self) -> bool {
        (self.eflags & OVERFLOW_FLAG) != 0
    }

    pub fn push32(&mut self, v: u32) {
        let addr = self.get_register(ESP).unwrap() - 4; //  (ESP - 4) is a next pointer of stack.
        self.set_register(ESP, addr);
        self.set_memory32(addr as usize, v);
    }

    pub fn pop32(&mut self) -> u32 {
        let addr = self.get_register(ESP).unwrap();
        let v = self.get_memory32(addr as usize);
        self.set_register(ESP, addr + 4);
        v.unwrap()
    }

    pub fn set_register(&mut self, i: usize, v: u32) {
        self.register.set(i, v);
    }

    pub fn get_register(&mut self, i: usize) -> Result<u32, Error> {
        Ok(self.register.get(i))
    }

    pub fn set_memory32(&mut self, i: usize, v: u32) {
        self.memory.set_u32(i, v)
    }

    pub fn read_imm8(&mut self) -> Result<u8, Error> {
        let v = self.memory.get_u8(self.eip as usize);
        self.eip += 1;
        v
    }

    pub fn read_imm8s(&mut self) -> Result<i8, Error> {
        let v = self.memory.get_i8(self.eip as usize);
        self.eip += 1;
        v
    }

    pub fn read_imm32s(&mut self) -> Result<i32, Error> {
        let v = self.memory.get_i32(self.eip as usize);
        self.eip += 4;
        v
    }

    pub fn read_imm32(&mut self) -> Result<u32, Error> {
        let v = self.memory.get_u32(self.eip as usize);
        self.eip += 4;
        v
    }
}
