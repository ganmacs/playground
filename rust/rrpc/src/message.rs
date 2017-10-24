#[derive(Serialize, Deserialize,  Debug)]
pub enum Message {
    Ping { id: u64, name: String, from: String },
    Ack { id: u64, name: String, from: String },
}
