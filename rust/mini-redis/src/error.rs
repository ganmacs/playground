use std::io;

#[derive(Debug)]
pub enum Error {
    IO(io::Error),
    Serialization(String),
    Invalid(String),
    RedisError(String),
}

impl Into<Error> for io::Error {
    fn into(self) -> Error {
        Error::IO(self)
    }
}
