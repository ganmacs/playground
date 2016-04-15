#[derive(Debug)]
pub struct Parser {
    pub v: i32,
    pub full_doc: String,
    pub usage: String,
}

impl Parser {
    pub fn new(doc: &str, value: i32) -> Result<Parser, String>{
        let p = Parser {
            v: value,
            full_doc: doc.to_owned(),
            usage: String::new(),
        };
        try!(p.validate());
        Ok(p)
    }

    fn validate(&self) -> Result<(), String>{
        if self.v < 0 {
            return Err("invalid status".to_owned());
        }
        return Ok(())
    }
}
