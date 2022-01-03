use crate::resp::Resp;
use bytes::Bytes;

#[derive(Debug)]
pub struct Get {
    key: String,
}

impl Get {
    pub fn new(key: impl ToString) -> Get {
        Get {
            key: key.to_string(),
        }
    }
}

impl From<Get> for Resp {
    fn from(get: Get) -> Self {
        let mut ary = Resp::array();
        ary.push_bulk_strings(Bytes::from("GET".as_bytes()));
        ary.push_bulk_strings(Bytes::from(get.key.into_bytes()));
        ary
    }
}
