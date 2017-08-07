use std::error;
use std::fmt;
use std::io;
use std::convert::From;

pub enum Error {
    MemoryOutOfRange(usize),
    UnknownOpcode(usize),
    IOError(io::Error),
    ModrmReg(u8),
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match *self {
            Error::MemoryOutOfRange(u) => format!("Memory out of range: {:X}", u).fmt(f),
            Error::UnknownOpcode(u) => format!("Unknow opcode: {:X}", u).fmt(f),
            Error::ModrmReg(u) => format!("ModR/M is out of range: {:X}", u).fmt(f),
            Error::IOError(ref e) => e.fmt(f),
        }
    }
}

impl fmt::Debug for Error {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match *self {
            Error::MemoryOutOfRange(u) => format!("Memory out of range: {:X}", u).fmt(f),
            Error::UnknownOpcode(u) => format!("Unknow opcode: {:X}", u).fmt(f),
            Error::IOError(ref e) => e.fmt(f),
            Error::ModrmReg(u) => format!("ModR/M is out of range: {:X}", u).fmt(f),
        }
    }
}

impl error::Error for Error {
    fn description(&self) -> &str {
        match *self {
            Error::MemoryOutOfRange(_) => "Memory out of range",
            Error::UnknownOpcode(_) => "Unknow opcode",
            Error::IOError(ref e) => e.description(),
            Error::ModrmReg(_) => "ModR/M is out of range", 
        }
    }
}

impl From<io::Error> for Error {
    fn from(error: io::Error) -> Self {
        Error::IOError(error)
    }
}
