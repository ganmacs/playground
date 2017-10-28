#[derive(Serialize, Deserialize,  Debug, Clone)]
pub enum Message {
    Ping { id: u64, to: String, from: String },
    Ack { id: u64, to: String, from: String },
}
