use std::env;
use std::result::Result;
use std::fs::File;
use std::io::{BufReader, Read, Bytes};
use std::io::{Error, ErrorKind};
use std::fmt;

enum Opcode {
    MOV(u8),
}

const REGISTER_COUNT: usize = 7;

impl fmt::Debug for Opcode {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match *self {
            Opcode::MOV(e) => write!(f, "{:X}", e),
        }
    }
}

impl Opcode {
    pub fn from_bin(op: u8) -> std::io::Result<Opcode> {
        match op {
            0xB8...0xBF => Ok(Opcode::MOV(op)),
            _ => Err(Error::new(ErrorKind::Other, "oh no!")),
        }
    }
}

struct Emulator<'a> {
    pub eip: u32,
    memory: Bytes<&'a [u8]>,
    registers: [u32; REGISTER_COUNT],
}

fn call_mov_r32_imm32(e: &mut Emulator, i: u8) {
    let reg = e.get_code().unwrap() - 0xB8;
    // let value = get_code32(emu, 1);

    unimplemented!()
}

impl<'a> Emulator<'a> {
    pub fn new(memory: Bytes<&'a [u8]>) -> Emulator<'a> {
        Emulator {
            memory: memory,
            eip: 0,
            registers: [0; REGISTER_COUNT],
        }
    }

    pub fn execute(&mut self, op: Opcode) {
        // duplciated
        match op {
            Opcode::MOV(e) => call_mov_r32_imm32(self, e),
            // _ => panic!("fooo"),
        }
    }


    pub fn inc_eip(&mut self) {
        self.eip += 1;
    }

    pub fn get_code(&mut self) -> std::io::Result<Opcode> {
        let v = self.memory.nth(self.eip as usize).unwrap()?;
        Opcode::from_bin(v)
    }

    pub fn get_code32(&mut self) -> std::io::Result<Opcode> {
        let v = self.memory.nth(self.eip as usize).unwrap()?;
        Opcode::from_bin(v)
    }

    pub fn get_code_i(&mut self, v: usize) -> std::io::Result<Opcode> {
        let v = self.memory.nth((self.eip as usize) + v).unwrap()?;
        Opcode::from_bin(v)
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

    let emu = &mut Emulator::new(buffer.bytes());

    while true {
        let code = emu.get_code()?;
        println!("EIP = {:?}, Code = {:?}\n", emu.eip, code);

        emu.execute(code);

        if emu.eip == 0x00 {
            println!("end of program");
            break;
        }
    }

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
