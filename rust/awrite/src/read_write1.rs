use byteorder::{ByteOrder, LittleEndian};
use bytes::{BufMut, BytesMut};
use std::collections::HashMap;
use std::{
    fs,
    io::Write,
    iter, marker, mem,
    sync::atomic,
    sync::{self, mpsc},
    thread, time,
};

const U16_SIZE: usize = mem::size_of::<u16>();

pub fn run() {
    let mut f = fs::File::open("rs.dump").unwrap();
    let mut w = AsyncWriter::new(f);
    w.start();

    for i in 0..100000 {
        w.add(&format!("key{:?}", i))
    }

    let sec = time::Duration::from_millis(1000 * 10);
    println!("Wait 1 sec");
}

type RW<T> = sync::Arc<sync::RwLock<T>>;

struct AsyncWriter<T> {
    buffer: RW<BytesMut>,
    writer: Option<T>,
    size: u64,
}

const BUFFER_LIMIT_SIZE: usize = 1024;
impl<T> AsyncWriter<T> {
    pub fn new(w: T) -> Self {
        Self {
            writer: Some(w),
            buffer: sync::Arc::new(sync::RwLock::new(BytesMut::with_capacity(
                BUFFER_LIMIT_SIZE * 2,
            ))),
            size: 0,
        }
    }
}

impl<T> AsyncWriter<T>
where
    T: Write + marker::Send + marker::Sync + 'static,
{
    pub fn start(&mut self) {
        let buf = self.buffer.clone();
        let mut writer = None;
        mem::swap(&mut self.writer, &mut writer);

        thread::Builder::new()
            .name("async writer".to_string())
            .spawn(move || {
                let mut writer = writer.unwrap();
                loop {
                    {
                        let b = buf.read().unwrap();
                        if b.len() > BUFFER_LIMIT_SIZE {
                            println!("flush");
                            writer.write(b.as_ref()).unwrap();
                        }
                    }

                    let sec = time::Duration::from_millis(1000);
                    println!("Wait 1 sec");
                    thread::sleep(sec);
                }
            })
            .unwrap();
    }

    pub fn add(&mut self, v: &str) {
        self.size += self.write_with_u32_prefix(v) as u64;
    }

    fn write_with_u32_prefix(&self, v: &str) -> usize {
        let mut buf = self.buffer.write().unwrap();
        buf.put_u16_le(v.len() as u16);
        buf.put(v);
        buf.len() + U16_SIZE
    }
}
