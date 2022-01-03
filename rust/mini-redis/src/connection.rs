use crate::error::Error;
use crate::resp::{ParseErr, Resp, RespWriter};
use bytes::{Buf, BytesMut};
use std::io::{Cursor, Error as IError, ErrorKind};
use tokio::io::{AsyncReadExt, AsyncWriteExt, BufWriter};
use tokio::net::TcpStream;

#[derive(Debug)]
pub struct Connection {
    stream: BufWriter<TcpStream>,

    // the buffer for reciving data
    buffer: BytesMut,
}

impl Connection {
    pub fn new(stream: TcpStream) -> Self {
        Connection {
            stream: BufWriter::new(stream),

            // TODO: capacity must be configurable
            buffer: BytesMut::with_capacity(4 * 1024),
        }
    }

    pub async fn write_data(&mut self, data: &Resp) -> Result<(), Error> {
        RespWriter::new(&mut self.stream)
            .write(data)
            .await
            .map_err(|e| e.into())?;

        self.stream.flush().await.map_err(|e| e.into())
    }

    pub async fn write_data2(&mut self, data: &[u8]) -> Result<(), Error> {
        self.stream.write(data).await.map_err(|e| e.into())?;
        self.stream.flush().await.map_err(|e| e.into())
    }

    pub async fn read_data(&mut self) -> Result<Option<Resp>, Error> {
        loop {
            if let Some(v) = self.parse_data()? {
                return Ok(Some(v));
            }

            let v = self
                .stream
                .read_buf(&mut self.buffer)
                .await
                .map_err(|e| e.into())?;

            if v == 0 {
                if self.buffer.is_empty() {
                    return Ok(None);
                } else {
                    return Err(Error::IO(IError::new(
                        ErrorKind::ConnectionReset,
                        "connection reset by peer",
                    )));
                }
            }
        }
    }

    fn parse_data(&mut self) -> Result<Option<Resp>, Error> {
        let mut buf = Cursor::new(&self.buffer[..]);

        if buf.has_remaining() {
            let len = buf.remaining();
            match Resp::parse(&mut buf) {
                Ok(resp) => {
                    // dicard already parased data
                    self.buffer.advance(len as usize);
                    return Ok(Some(resp));
                }
                // still waiting for data
                Err(ParseErr::Imcomplete) => Ok(None),
                Err(e) => Err(Error::Serialization(format!("{:?}", e).into())), // TODO
            }
        } else {
            return Ok(None);
        }
    }
}
