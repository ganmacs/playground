extern crate bytes;
extern crate crc;
extern crate rand;

mod log;
mod batch;
mod memdb;
mod ikey;

use batch::WriteBatch;
use log::{LogReader, LogWriter};
use memdb::MemDB;
use ikey::InternalKey;
use std::fs;

pub struct LogDB {
    log: LogWriter,
    dir: String,
    version: Version,
    mem: MemDB,
}

struct Version {
    file_number: u64,
}

impl Version {
    pub fn new() -> Self {
        Version { file_number: 0 }
    }

    pub fn next_file_num(&mut self) -> u64 {
        let x = self.file_number;
        self.file_number += 1;
        x
    }

    pub fn file_num(&self) -> u64 {
        self.file_number
    }
}

pub fn open(dir: &str) -> LogDB {
    let mut db = LogDB::open(dir);
    db.recover();
    db
}

enum FileType {
    Log,
}

impl FileType {
    pub fn filename(&self, dir: &str, num: u64) -> String {
        match self {
            Log => format!("{:}/{:07}.log", dir, num),
        }
    }
}

impl LogDB {
    fn open(dir: &str) -> Self {
        if let Err(err) = fs::create_dir(&dir) {
            println!("Skip create directory {:?}", err);
        };

        let mut v = Version::new();
        let fname = FileType::Log.filename(dir, v.next_file_num());
        let fd = fs::OpenOptions::new() // add read permission?
            .write(true)
            .create(true)
            .open(fname)
            .unwrap();

        LogDB {
            dir: dir.to_owned(),
            log: LogWriter::new(fd),
            version: v,
            mem: MemDB::new(),
        }
    }

    pub fn get(&self, key: &str) -> Option<String> {
        let ikey = InternalKey::new(key, 0); // XXX use actual seq
        let ret = self.mem.get(&ikey);
        if let Some(v) = ret { Some(v) } else { None }
    }

    pub fn set(&mut self, key: &str, value: &str) {
        let mut b = WriteBatch::new();
        b.put(key, value);
        self.apply(b)
    }

    pub fn recover(&mut self) {
        let paths = fs::read_dir(&self.dir).unwrap();
        for path in paths {
            self.replay_logfile(&path.unwrap().path());
        }
    }

    fn replay_logfile(&mut self, path: &std::path::PathBuf) {
        let fd = fs::File::open(path).unwrap();
        let mut lr = LogReader::new(fd);
        let record = lr.read_record().unwrap();
        let write_batch = WriteBatch::load_data(record);

        for (key_kind, ukey, value) in write_batch.into_iter() {
            self.mem.add(key_kind, ukey, value);
        }
    }

    fn apply(&mut self, batch: WriteBatch) {
        self.log.add_record(batch.data());

        for (key_kind, ukey, value) in batch.into_iter() {
            self.mem.add(key_kind, ukey, value);
        }
    }
}
