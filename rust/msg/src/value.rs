pub mod float;
mod from;
pub mod integer;
mod pack;

#[derive(Clone, PartialEq, Debug)]
pub enum Value {
    // represents an integer
    Integer(integer::Integer),

    // represents nil
    Nil,

    // represents true or false
    Boolean(bool),

    // represents a IEEE 754 double precision floating point number including NaN and Infinity
    Float(float::Float),

    // Raw. extending Raw type represents a byte array
    Binary(Vec<u8>),

    // Raw. extending Raw type represents a UTF-8 string
    String(String),

    // represents a sequence of objects
    Array(Vec<Value>),

    // represents key-value pairs of objects
    Map,

    // represents a tuple of type information and a byte array where type information is an integer whose meaning is defined by applications or MessagePack specification
    Extension,
    // represents an instantaneous point on the time-line in the world that is independent from time zones or calendars. Maximum precision is nanoseconds.
    Timestamp,
}
