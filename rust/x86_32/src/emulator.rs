// use errors::Error;
use memory::{Memory, INITIAL_INDEX, MEMORY_SIZE};
use errors::Error;
use std::io::{BufReader, Read};
use std::fs::File;

const REGISTER_COUNT: usize = 8;
const REGISTER_NAME: [&str; 8] = ["EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"];

pub struct Emulator<'a> {
    pub eip: u32,
    memory: Memory<'a>,
    registers: [u32; REGISTER_COUNT],
}

pub fn run(file_path: String) -> Result<(), Error> {
    let file = File::open(file_path)?;
    let mut binary = [0; MEMORY_SIZE + INITIAL_INDEX];
    BufReader::new(file).read(&mut binary[INITIAL_INDEX..])?;

    let mem = Memory::new(&binary);
    let emu = &mut Emulator::new(mem, INITIAL_INDEX as u32);
    emu.run()
}

impl<'a> Emulator<'a> {
    pub fn new(memory: Memory<'a>, esp: u32) -> Emulator<'a> {
        let mut emu = Emulator {
            memory: memory,
            eip: 0x7c00,
            registers: [0; REGISTER_COUNT],
        };

        // esp
        emu.registers[4] = esp;
        emu
    }

    pub fn run(&mut self) -> Result<(), Error> {
        loop {
            let code = self.get_code8(0)?;
            println!("EIP = {:X}, Code = {:X}", self.eip, code);

            self.exec(code)?;

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
            0xB8...0xBF => self.mov_r32_imm32(),
            0xE9 => self.jmp_rel32(),
            0xEB => self.jmp_rel8(),
            _ => Err(Error::UnknownOpcode(op as usize)),
        }
    }

    fn mov_r32_imm32(&mut self) -> Result<(), Error> {
        let reg: u8 = self.get_code8(0)? - 0xB8;
        let value: u32 = self.get_code32(1).unwrap();
        self.registers[reg as usize] = value;
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

    fn dump(&mut self) {
        for i in 0..REGISTER_COUNT {
            println!("{} {:08X}", REGISTER_NAME[i], self.registers[i]);
        }

        println!("ESP {:08X}", self.eip);
    }

    fn get_code32(&mut self, i: usize) -> Result<u32, Error> {
        self.memory.get_u32(self.eip as usize + i)
    }

    fn get_sign_code32(&mut self, i: usize) -> Result<i32, Error> {
        self.memory
            .get_u32(self.eip as usize + i)
            .map(|v| v as i32)
    }

    fn get_code8(&mut self, i: usize) -> Result<u8, Error> {
        self.memory.get_u8(self.eip as usize + i)
    }

    fn get_sign_code8(&mut self, i: usize) -> Result<i8, Error> {
        self.memory.get_i8(self.eip as usize + i)
    }
}
