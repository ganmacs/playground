// use errors::Error;
use memory::{Memory, INITIAL_INDEX};
use errors::Error;
use register::*;
use instruction;
use std::io::BufReader;
use std::fs::File;

pub struct Emulator {
    pub eip: u32,
    memory: Memory,
    register: Register,
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
        };

        emu.register.set(ESP, esp);
        emu
    }

    pub fn run(&mut self) -> Result<(), Error> {
        loop {
            let code = self.get_code8(0)?;
            println!("EIP = {:02X}, Code = {:02X}", self.eip, code);

            self.exec(code)?;
            self.dump();

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
            0x50...0x57 => instruction::push_r32(self),
            0x58...0x59 => instruction::pop_r32(self),
            0x83 => instruction::opcode_83(self),
            0x89 => instruction::mov_rm32_r32(self),
            0x8B => instruction::mov_r32_rm32(self),
            0xB8...0xBF => self.mov_r32_imm32(),
            0xC3 => instruction::ret(self),
            0xC7 => instruction::mov_rm32_imm32(self),
            0xC9 => instruction::leave(self),
            0xE8 => instruction::call_rel32(self),
            0xE9 => self.jmp_rel32(),
            0xEB => self.jmp_rel8(),
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

    fn jmp_rel32(&mut self) -> Result<(), Error> {
        let n: i32 = self.get_code32(1)? as i32;
        let v = (n as i64) + 5 + (self.eip as i64); // XXX
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
