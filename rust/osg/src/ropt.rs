use parser::Parser;
use std::{process, fmt, env};
use self::Error::Usage;

#[derive(Debug)]
pub enum Error {
    Usage(String)
}

impl Error {
    pub fn is_fotal(&self) -> bool {
        match *self {
            Usage(..) => true,
        }
    }

    pub fn exit(&self) -> ! {
        if self.is_fotal() {
            println!("{}", self);
            process::exit(1)
        } else {
            println!("{}", self);
            process::exit(0)
        }
    }
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match *self {
            Usage(ref s) => write!(f, "{}", s),
        }
    }
}

#[derive(Debug)]
pub struct Ropt {
    pub p: Parser,
    pub argv: Option<Vec<String>>
}

impl Ropt {
    pub fn new<S>(s: S) -> Result<Ropt, Error>
        where S: ::std::ops::Deref<Target=str> {
        Parser::new(s.deref(), 1)
            .map_err(Usage)
            .map(|p| Ropt {
                argv: None,
                p: p,
            })
    }

    pub fn decode(mut self) -> Result<Ropt, Error> {
        println!("{:?}", Ropt::get_argv());
        Ok(self)
    }


    pub fn get_argv() -> Vec<String> {
        env::args().skip(1).collect()
    }
}
