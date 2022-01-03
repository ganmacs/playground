use crate::resp::Resp;
use bytes::Bytes;

#[derive(Debug)]
pub struct Ping {}

impl Ping {
    pub fn new() -> Self {
        Ping {}
    }
}

impl From<Ping> for Resp {
    fn from(_ping: Ping) -> Self {
        let mut ary = Resp::array();
        ary.push_bulk_strings(Bytes::from("PING"));
        ary
    }
}
