#[derive(Debug)]
pub struct Option {
    pub action: i32
}

impl Option {
    pub fn new() -> Option {
        Option { action:  10 }
    }
}
