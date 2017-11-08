use message::Message;
use bytes::BytesMut;
use bytes::BufMut;
use serde_json;
use tokio_io::codec::{Encoder, Decoder};
use std::io;

pub struct JsonCodec;

impl Decoder for JsonCodec {
    type Item = Message;
    type Error = io::Error;

    fn decode(&mut self, src: &mut BytesMut) -> Result<Option<Self::Item>, Self::Error> {
        let decoded = serde_json::from_slice(&src).map_err(|e| {
            io::Error::new(io::ErrorKind::Other, e)
        })?;
        Ok(Some(decoded))
    }
}

impl Encoder for JsonCodec {
    type Item = Message;
    type Error = io::Error;

    fn encode(&mut self, item: Self::Item, buf: &mut BytesMut) -> Result<(), Self::Error> {
        serde_json::to_writer(buf.writer(), &item).map_err(|e| {
            io::Error::new(io::ErrorKind::Other, e)
        })
    }
}
