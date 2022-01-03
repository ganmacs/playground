use mini_redis::{client, error::Error as RErr};

#[tokio::main]
pub async fn main() -> Result<(), RErr> {
    let mut client = client::connection("127.0.0.1:6379").await?;
    client.ping().await?;

    let r = client.set("key1", "value".into()).await?;
    dbg!(r);

    let r = client.get("key").await?;
    dbg!(r);

    let r = client.get("key1").await?;
    dbg!(r);

    Ok(())
}
