extern crate getopts;

use std::fmt;

pub struct Options {
    pub matches:  getopts::Matches
}

impl Options {
    pub fn parse(args: &Vec<String>) -> Result<Options, ErrStat>{
        let opts = Options::build_opts();

        let matches: getopts::Matches = match opts.parse(args) {
            Ok(m) => m,
            Err(e) => return Err(ErrStat::InvalidOptions(e))
        };

        if matches.opt_present("help") {
            let mut msg: String = USAGE.to_owned();
            if !matches.opt_present("long") {
                msg.push_str(OPTIONS);
            }

            return Err(ErrStat::Help(msg))
        }
        else if matches.opt_present("version") {
            return Err(ErrStat::Version)
        }

        return Ok(Options { matches: matches })
    }

    fn build_opts() -> getopts::Options {
        let mut opts = getopts::Options::new();
        opts.optflag("v", "version", "display version of ex");
        opts.optflag("h", "help", "show list of command line options");

        // long
        opts.optflag("l", "long", "display extended details and attribues");
        return opts
    }
}

static USAGE:  &'static str = "Usage:\n  exa [options] [files...]\n";

static OPTIONS: &'static str = r##"
DISPLAY OPTINS
  -l, --long         display extended details and attributes
"##;


#[derive(Debug)]
pub enum ErrStat {
    Version,
    Help(String),
    InvalidOptions(getopts::Fail)
}

impl ErrStat {
    pub fn exit_code(&self) -> i32{
        match *self {
            ErrStat::Help(_) => 0,
            ErrStat::Version => 0,
            _ => 3
        }
    }
}

impl fmt::Display for ErrStat {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        use self::ErrStat::*;
        match *self {
            InvalidOptions(ref fail) => write!(f, "{}", fail),
            Help(ref text) => write!(f, "{}", text),
            Version => write!(f, "ex {}", env!("CARGO_PKG_VERSION"))
        }
    }
}
