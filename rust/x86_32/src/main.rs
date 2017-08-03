extern crate x86_32;

use std::env;
use std::result::Result;
use std::fs::File;
use std::io::{BufReader, Read};
use x86_32::errors::Error;

enum Opcode {
    Mov(u8),
    JmpRel8,
    JmpRel32,
}

const REGISTER_COUNT: usize = 8;
const REGISTER_NAME: [&str; 8] = ["EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"];
const INITIAL_MEMORY_I: usize = 0x7c00;
const MEMORY_SIZE: usize = 1024 * 1024;

impl Opcode {
    pub fn from_bin(op: u8) -> Result<Opcode, Error> {
        match op {
            0xB8...0xBF => Ok(Opcode::Mov(op)),
            0xEB => Ok(Opcode::JmpRel8),
            0xE9 => Ok(Opcode::JmpRel32),
            _ => Err(Error::UnknownOpcode(op as usize)),
        }
    }
}

struct Emulator<'a> {
    pub eip: u32,
    memory: x86_32::memory::Memory<'a>,
    registers: [u32; REGISTER_COUNT],
}

fn mov_r32_imm32(e: &mut Emulator) {
    let reg: u8 = e.get_code().unwrap() - 0xB8;
    let value: u32 = e.get_code32(1 as usize).unwrap();
    e.registers[reg as usize] = value;
    e.eip += 5;
}

fn jmp_rel8(e: &mut Emulator) {
    let rel = e.get_sign_code(1).unwrap();
    // rel can be minus value
    let v = (2 + rel) as i64 + (e.eip as i64); // XXX
    e.eip = v as u32;
}

fn jmp_rel32(e: &mut Emulator) {
    let n: i32 = e.get_code32(1).unwrap() as i32;
    let v = (n as i64) + 5 + (e.eip as i64); // XXX
    e.eip = v as u32 // rel + op
}

impl<'a> Emulator<'a> {
    pub fn new(memory: x86_32::memory::Memory<'a>, esp: u32) -> Emulator<'a> {
        let mut emu = Emulator {
            memory: memory,
            eip: 0x7c00,
            registers: [0; REGISTER_COUNT],
        };

        // esp
        emu.registers[4] = esp;
        emu
    }

    pub fn execute(&mut self, op: Opcode) {
        // duplciated
        match op {
            Opcode::Mov(_) => mov_r32_imm32(self),
            Opcode::JmpRel8 => jmp_rel8(self),
            Opcode::JmpRel32 => jmp_rel32(self),
            // _ => panic!("fooo"),
        }
    }

    pub fn dump(&mut self) {
        for i in 0..REGISTER_COUNT {
            println!("{} {:08X}", REGISTER_NAME[i], self.registers[i]);
        }
        println!("ESP {:08X}", self.eip);
    }

    pub fn get_sign_code(&mut self, i: usize) -> Result<i8, Error> {
        self.memory.get_i8(self.eip as usize + i)
    }

    pub fn get_code_i(&mut self, v: usize) -> Result<u8, Error> {
        self.memory.get_u8(self.eip as usize + v)
    }

    pub fn get_code(&mut self) -> Result<u8, Error> {
        self.memory.get_u8(self.eip as usize)
    }

    pub fn get_code32(&mut self, index: usize) -> Result<u32, Error> {
        self.memory.get_u32(self.eip as usize + index)
    }
}

fn main() {
    let status = match get_file_name() {
        Err(v) => {
            println!("{:?}", v);
            1
        }
        Ok(v) => {
            println!("{:?}", run(v)); // TODO
            0
        }
    };

    std::process::exit(status)
}

fn run(v: String) -> Result<(), Error> {
    println!("{:?}", v);

    let f = File::open(v)?;
    let mut f = BufReader::new(f);

    let mut buffer = [0; 512 + INITIAL_MEMORY_I];
    f.read(&mut buffer[0x7c00..])?;

    let v = x86_32::memory::Memory::new(&buffer);

    let emu = &mut Emulator::new(v, INITIAL_MEMORY_I as u32);

    while true {
        let code = emu.get_code()?;

        println!("EIP = {:X}, Code = {:X}", emu.eip, code);
        Opcode::from_bin(code).map(|v| emu.execute(v))?;

        if emu.eip == 0x00 {
            println!("end of program");
            break;
        }
    }

    emu.dump();
    Ok(())
}


fn get_file_name() -> Result<String, &'static str> {
    let args: Vec<_> = env::args().skip(1).collect();
    if args.len() <= 0 {
        Err("Usage: x86_32 <filename>")
    } else {
        Ok(args[0].to_owned())
    }
}
