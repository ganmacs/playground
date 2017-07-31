use std::env;
use std::result::Result;
use std::fs::File;
use std::io::{BufReader, Read, Bytes};
use std::io::{Error, ErrorKind};
use std::fmt;

enum Opcode {
    MOV(u8),
    JMP_REL8,
}

const REGISTER_COUNT: usize = 8;
const REGISTER_NAME: [&str; 8] = ["EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"];

impl Opcode {
    pub fn from_bin(op: u8) -> std::io::Result<Opcode> {
        match op {
            0xB8...0xBF => Ok(Opcode::MOV(op)),
            0xEB => Ok(Opcode::JMP_REL8),
            _ => Err(Error::new(ErrorKind::Other, "oh no!")),
        }
    }
}

struct Emulator {
    pub eip: u32,
    memory: [u8; 512], // u8 should be type parameter, and size of array
    registers: [u32; REGISTER_COUNT],
}

fn mov_r32_imm32(e: &mut Emulator, i: u8) {
    let reg: u8 = e.get_code().unwrap() - 0xB8;
    let value: u32 = e.get_code32(1).unwrap();
    e.registers[reg as usize] = value;
    e.eip += 5;
}

fn jmp_rel8(e: &mut Emulator) {
    let rel = e.get_sign_code(1).unwrap();
    // rel can be minus value
    let v = (2 + rel) as i64 + (e.eip as i64); // XXX
    e.eip = (v as u32);
}

impl Emulator {
    pub fn new(memory: [u8; 512], esp: u32) -> Emulator {
        let mut emu = Emulator {
            memory: memory,
            eip: 0,
            registers: [0; REGISTER_COUNT],
        };

        // esp
        emu.registers[4] = esp;
        emu
    }

    pub fn execute(&mut self, op: Opcode) {
        // duplciated
        match op {
            Opcode::MOV(e) => mov_r32_imm32(self, e),
            Opcode::JMP_REL8 => jmp_rel8(self),
            // _ => panic!("fooo"),
        }
    }

    pub fn dump(&mut self) {
        for i in 0..REGISTER_COUNT {
            println!("{} {:08X}", REGISTER_NAME[i], self.registers[i]);
        }
        println!("ESP {:08X}", self.eip);
    }

    pub fn inc_eip(&mut self) {
        self.eip += 1;
    }

    pub fn get_sign_code(&mut self, i: usize) -> std::io::Result<i8> {
        let v = self.memory[self.eip as usize + i];
        Ok(v as i8)
    }

    pub fn get_code(&mut self) -> std::io::Result<u8> {
        let v = self.memory[self.eip as usize];
        Ok(v)
    }

    pub fn get_code32(&mut self, index: usize) -> std::io::Result<u32> {
        let mut ret: u32 = 0;

        for i in 0..4 {
            ret |= self.get_code_i(i + index)
                .map(|v| v as u32)
                .map(|v| v << (i * 8))
                .unwrap(); // XXX: unwrap
        }

        Ok(ret)
    }

    pub fn get_code_i(&mut self, v: usize) -> std::io::Result<u8> {
        Ok(self.memory[self.eip as usize + v])
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

fn run(v: String) -> std::io::Result<()> {
    println!("{:?}", v);

    let f = File::open(v)?;
    let mut f = BufReader::new(f);

    let mut buffer = [0; 512];
    f.read(&mut buffer)?;

    let emu = &mut Emulator::new(buffer, 0x7c00);

    while true {
        let code = emu.get_code()?;

        println!("EIP = {:?}, Code = {:X}", emu.eip, code);
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
