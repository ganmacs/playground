use bytes::{Buf, Bytes};
use std::io::{self, Cursor};
use tokio::io::AsyncWriteExt;

// REdis Serialization Protocol
#[derive(Debug)]
pub enum Resp {
    SimpleString(String),
    Error(String),
    Integer(i64),
    BulkString(Bytes),
    Array(Vec<Resp>),
    Null,
}

#[derive(Debug)]
pub enum ParseErr {
    Imcomplete,
    Invalid(String),
}

const SIMPLE_STRING_CHAR: u8 = b'+';
const BULK_STRING_CHAR: u8 = b'$';
const INTEGER_CHAR: u8 = b':';
const ERROR_CHAR: u8 = b'-';
const ARRAY_CHAR: u8 = b'*';

fn read_u8(buf: &mut Cursor<&[u8]>) -> Result<u8, ParseErr> {
    let v = peek_u8(buf)?;
    buf.advance(1);

    Ok(v)
}

fn peek_u8(buf: &Cursor<&[u8]>) -> Result<u8, ParseErr> {
    if !buf.has_remaining() {
        return Err(ParseErr::Imcomplete);
    }

    return Ok(buf.chunk()[0]);
}

fn read_num(buf: &mut Cursor<&[u8]>) -> Result<i64, ParseErr> {
    use atoi::atoi;

    let mut negtive = false;
    if peek_u8(buf)? == b'-' {
        skip(buf, 1)?; // skip '-'

        negtive = true;
    }

    let line = read_line(buf)?;
    let r = atoi::<i64>(line).ok_or_else(|| ParseErr::Invalid("invalid protocol".into()))?;

    if negtive {
        Ok(-1 * r)
    } else {
        Ok(r)
    }
}

fn read_string(buf: &mut Cursor<&[u8]>) -> Result<String, ParseErr> {
    let line = read_line(buf)?.to_vec();

    String::from_utf8(line).map_err(|e| ParseErr::Invalid(e.to_string()))
}

fn skip(buf: &mut Cursor<&[u8]>, n: usize) -> Result<(), ParseErr> {
    if buf.remaining() < n {
        return Err(ParseErr::Imcomplete);
    }

    buf.advance(n);
    return Ok(());
}

fn read_line<'a>(buf: &mut Cursor<&'a [u8]>) -> Result<&'a [u8], ParseErr> {
    let start = buf.position() as usize;
    let end = buf.get_ref().len();

    for i in start..(end - 1) {
        if buf.get_ref()[i] == b'\r' && buf.get_ref()[i + 1] == b'\n' {
            buf.set_position(std::cmp::min(i + 2, end) as u64);

            // without \r\n
            return Ok(&buf.get_ref()[start..i]);
        }
    }

    Err(ParseErr::Imcomplete)
}

impl Resp {
    pub fn parse(buf: &mut Cursor<&[u8]>) -> Result<Resp, ParseErr> {
        match read_u8(buf)? {
            BULK_STRING_CHAR => {
                match read_num(buf)? {
                    -1 => Ok(Resp::Null),
                    len if len < -1 => Err(ParseErr::Invalid(
                        "invalid protocol. negitive value is not allowed here".into(),
                    )),
                    len => {
                        let len = len as usize;
                        if buf.remaining() < len {
                            return Err(ParseErr::Imcomplete);
                        }
                        let r = Bytes::copy_from_slice(&buf.chunk()[..len]);
                        skip(buf, len + 2)?; // expected \r\n

                        Ok(Resp::BulkString(r))
                    }
                }
            }
            SIMPLE_STRING_CHAR => {
                let sstring = read_string(buf)?;
                Ok(Resp::SimpleString(sstring))
            }
            INTEGER_CHAR => {
                let n = read_num(buf)?;
                Ok(Resp::Integer(n))
            }
            ARRAY_CHAR => match read_num(buf)? {
                -1 => Ok(Resp::Null),
                len if len < -1 => Err(ParseErr::Invalid("invalid protocol".into())),
                len => {
                    let len = len as usize;
                    let mut inner = Vec::with_capacity(len);
                    for _ in 0..len {
                        inner.push(Resp::parse(buf)?)
                    }

                    Ok(Resp::Array(inner))
                }
            },
            ERROR_CHAR => {
                let sstring = read_string(buf)?;
                Ok(Resp::Error(sstring))
            }
            actual => {
                println!("{:?}", actual);
                Err(ParseErr::Imcomplete)
            }
        }
    }

    pub fn array() -> Resp {
        Resp::Array(vec![])
    }

    pub fn push_bulk_strings(&mut self, buf: Bytes) {
        match self {
            Resp::Array(r) => r.push(Resp::BulkString(buf)),
            _ => panic!("type mismatched"),
        }
    }

    pub fn push_simple_strings(&mut self, buf: String) {
        match self {
            Resp::Array(r) => r.push(Resp::SimpleString(buf)),
            _ => panic!("type mismatched"),
        }
    }

    pub fn push_integers(&mut self, v: i64) {
        match self {
            Resp::Array(r) => r.push(Resp::Integer(v)),
            _ => panic!("type mismatched"),
        }
    }
}

pub struct RespWriter<'a, T> {
    inner: &'a mut T,
}

impl<'a, T> RespWriter<'a, T> {
    pub fn new(inner: &'a mut T) -> RespWriter<'a, T> {
        RespWriter { inner }
    }
}

impl<'a, T: AsyncWriteExt + std::marker::Unpin> RespWriter<'a, T> {
    pub async fn write(&mut self, data: &Resp) -> io::Result<()> {
        match data {
            Resp::Array(vals) => {
                self.inner.write_u8(b'*').await?;
                write_num(self.inner, vals.len()).await?;
                for item in vals {
                    self.write_value(item).await?;
                }
            }
            _ => self.write_value(data).await?, // to avoid boxing in async fn
        }

        Ok(())
    }

    async fn write_value(&mut self, data: &Resp) -> io::Result<()> {
        match data {
            Resp::BulkString(val) => {
                self.inner.write_u8(BULK_STRING_CHAR).await?;
                write_num(self.inner, val.len()).await?;
                self.inner.write_all(val).await?;
                self.inner.write_all(b"\r\n").await?;
            }
            Resp::SimpleString(val) => {
                self.inner.write_u8(SIMPLE_STRING_CHAR).await?;
                self.inner.write_all(val.as_bytes()).await?;
                self.inner.write_all(b"\r\n").await?;
            }

            Resp::Array(_) => unreachable!(),
            _ => todo!(),
        }
        Ok(())
    }
}

async fn write_num<T: AsyncWriteExt + std::marker::Unpin>(
    dst: &mut T,
    val: usize,
) -> io::Result<()> {
    dst.write_all(val.to_string().as_bytes()).await?;
    dst.write_all(b"\r\n").await?;
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[tokio::test]
    async fn write_simple_string() {
        let mut buf = vec![];
        RespWriter::new(&mut buf)
            .write(&Resp::SimpleString("OK".into()))
            .await
            .unwrap();

        assert_eq!(b"+OK\r\n".to_vec(), buf);
    }

    #[tokio::test]
    async fn write_bulk_string() {
        let mut buf = vec![];
        RespWriter::new(&mut buf)
            .write(&Resp::BulkString("OK".into()))
            .await
            .unwrap();

        assert_eq!(b"$2\r\nOK\r\n".to_vec(), buf);
    }

    #[tokio::test]
    async fn write_array() {
        let mut buf = vec![];

        let mut inner = vec![];
        inner.push(Resp::SimpleString("OK1".into()));
        inner.push(Resp::BulkString("OK2".into()));
        let resp = Resp::Array(inner);
        RespWriter::new(&mut buf).write(&resp).await.unwrap();

        assert_eq!(b"*2\r\n+OK1\r\n$3\r\nOK2\r\n".to_vec(), buf);
    }
}
