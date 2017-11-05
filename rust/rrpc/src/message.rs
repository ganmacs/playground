#[derive(Serialize, Deserialize,  Debug, Clone)]
pub enum Message {
    Ping { id: u64, to: String, from: String },
    Ack { id: u64, to: String, from: String },
}

// impl Message {
//     pub fn to_ack<T: Into<String>>(name: &T, m: &Message) -> Message::Ack {
//         match m {
//             Message::Ping { id, to, from } => Message::Ack,
//         }


//     }
// }
