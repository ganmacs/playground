use crate::error::Error;
use crate::{command, connection::Connection, resp::Resp};
use bytes::Bytes;
use tokio::net::{TcpStream, ToSocketAddrs};

#[derive(Debug)]
pub struct Client {
    connection: Connection,
}

pub async fn connection<T: ToSocketAddrs>(addr: T) -> Result<Client, Error> {
    let stream = TcpStream::connect(addr).await.map_err(|e| e.into())?;
    let connection = Connection::new(stream);

    Ok(Client { connection })
}

impl Client {
    pub async fn ping(&mut self) -> Result<(), Error> {
        let ping = Resp::from(command::Ping::new());
        self.connection.write_data(&ping).await?;

        match self.read_response().await? {
            Resp::SimpleString(resp) if resp == "PONG" => Ok(()),
            rest => Err(Error::Invalid(
                format!("invalid response ${:?}", rest).into(),
            )),
        }
    }

    pub async fn set(&mut self, key: &str, value: Bytes) -> Result<Option<()>, Error> {
        let set = Resp::from(command::Set::new(key, value));
        self.connection.write_data(&set).await?;

        let r = self.read_response().await?;
        dbg!(&r);
        match r {
            Resp::SimpleString(resp) if resp == "OK" => Ok(None),
            rest => Err(Error::Invalid(
                format!("invalid response ${:?}", rest).into(),
            )),
        }
    }

    pub async fn get(&mut self, key: &str) -> Result<Option<Bytes>, Error> {
        let get = Resp::from(command::Get::new(key));
        self.connection.write_data(&get).await?;
        match self.read_response().await? {
            Resp::SimpleString(resp) => Ok(Some(resp.into())),
            Resp::BulkString(resp) => Ok(Some(resp)),
            Resp::Null => Ok(None),
            rest => Err(Error::Invalid(
                format!("invalid response ${:?}", rest).into(),
            )),
        }
    }

    pub async fn incr(&mut self, key: &str) -> Result<i64, Error> {
        let incr = Resp::from(command::Incr::new(key));
        self.connection.write_data(&incr).await?;
        self.handle_incr_decr_resp().await
    }

    pub async fn decr(&mut self, key: &str) -> Result<i64, Error> {
        let incr = Resp::from(command::Decr::new(key));
        self.connection.write_data(&incr).await?;
        self.handle_incr_decr_resp().await
    }

    async fn handle_incr_decr_resp(&mut self) -> Result<i64, Error> {
        match self.read_response().await? {
            Resp::Integer(resp) => Ok(resp),
            Resp::Error(msg) => Err(Error::RedisError(msg)),
            rest => Err(Error::Invalid(
                format!("invalid response ${:?}", rest).into(),
            )),
        }
    }

    async fn read_response(&mut self) -> Result<Resp, Error> {
        let resp = self.connection.read_data().await?;
        match resp {
            Some(r) => Ok(r),
            None => Err(Error::Invalid("invalid state".into())),
        }
    }
}
