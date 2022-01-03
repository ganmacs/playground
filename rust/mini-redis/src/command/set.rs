use crate::resp::Resp;
use bytes::Bytes;

#[derive(Debug)]
pub struct Set {
    key: String,
    value: Bytes,
}

impl Set {
    pub fn new(key: impl ToString, value: Bytes) -> Self {
        Set {
            key: key.to_string(),
            value,
        }
    }
}

impl From<Set> for Resp {
    fn from(set: Set) -> Self {
        let mut ary = Resp::array();
        ary.push_bulk_strings(Bytes::from("SET".as_bytes()));
        ary.push_bulk_strings(Bytes::from(set.key.into_bytes()));
        ary.push_bulk_strings(set.value);
        ary
    }
}
