use bytes::{BytesMut, Bytes, BufMut, LittleEndian, ByteOrder};

pub struct InternalKey {
    inner: Bytes,
}

const UKEY_LENGTH: usize = 4;
const SEQ_LENGTH: usize = 8;
const UKEY_INDEX: usize = 4;

impl InternalKey {
    pub fn new(user_key: &str, seq: u64) -> Self {
        let size = user_key.len();
        let mut bytes = BytesMut::with_capacity(UKEY_LENGTH + size + SEQ_LENGTH);
        bytes.put_u32::<LittleEndian>(size as u32);
        bytes.put_slice(user_key.as_bytes());
        bytes.put_u64::<LittleEndian>(seq);
        bytes.put_u64::<LittleEndian>(seq);

        InternalKey { inner: bytes.freeze() }
    }

    pub fn user_key(&self) -> Bytes {
        let size = self.key_size();
        self.inner.slice(UKEY_INDEX, UKEY_INDEX + size)
    }

    pub fn seq_number(&self) -> usize {
        let seq_idx = self.key_size() + UKEY_INDEX;
        let val = self.inner.slice(seq_idx, seq_idx + SEQ_LENGTH);
        LittleEndian::read_u64(&val) as usize
    }

    fn key_size(&self) -> usize {
        let v = self.inner.slice_to(4);
        LittleEndian::read_u32(&v) as usize
    }
}

#[cfg(test)]
mod tests {
    use super::InternalKey;

    #[test]
    fn test_internal_key() {
        let ikey = InternalKey::new("hoge", 100);
        assert_eq!(ikey.user_key(), "hoge");
        assert_eq!(ikey.seq_number(), 100);
    }
}
