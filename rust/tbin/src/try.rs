use std::num::ParseIntError;
use std::fmt;

type Result<T> = std::result::Result<T, DoubleError>;

#[derive(Debug)]
enum DoubleError {
    EmptyVec,
    Parse(ParseIntError),
}

impl From<ParseIntError> for DoubleError {
    fn from(err: ParseIntError) -> DoubleError {
        DoubleError::Parse(err)
    }
}

impl fmt::Display for DoubleError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match *self {
            DoubleError::EmptyVec => write!(f, "hogehoge"),
            DoubleError::Parse(ref e) => e.fmt(f),
        }
    }
}

fn double_first(vec: Vec<&str>) -> Result<i32> {
    let first = try!(vec.first().ok_or(DoubleError::EmptyVec));
    let parsed = try!(first.parse::<i32>());
    Ok(2 * parsed)
}

fn print(r: Result<i32>) {
    println!("{:?}", r);
    match r {
        Ok(n) => println!("{}", n),
        Err(e) => println!("{}", e),
    }
}

fn main() {
    let numbers = vec!["as"];
    print(double_first(numbers));
    let a = None::<i32>;
    println!("{:?}", a);
    let collected_iterator: Vec<i32> = (0..10).collect();
    println!("{:?}", collected_iterator);
}
