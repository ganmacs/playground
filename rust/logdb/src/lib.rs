extern crate bytes;
extern crate crc;

mod log;
mod batch;

use batch::WriteBatch;
use log::{LogReader, LogWriter};
use std::fs;

pub struct LogDB {
    log: LogWriter,
    dir: String,
    version: Version,
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
    let db = LogDB::open(dir);
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
        let fd = fs::OpenOptions::new()
            .write(true)
            .create(true)
            .open(fname)
            .unwrap();
        let log = fd.try_clone().map(|fd| LogWriter::new(fd)).unwrap();

        LogDB {
            dir: dir.to_owned(),
            log: log,
            version: v,
        }
    }

    pub fn set(&mut self, key: &str, value: &str) {
        let mut b = WriteBatch::new();
        b.put(key, value);
        self.apply(b)
    }

    pub fn recover(&self) {
        let paths = fs::read_dir(&self.dir).unwrap();
        for path in paths {
            self.replay_logfile(&path.unwrap().path());
        }
    }

    fn replay_logfile(&self, path: &std::path::PathBuf) {
        println!("{:?}", path);
        let fd = fs::File::open(path).unwrap();
        let mut lr = LogReader::new(fd);
        lr.read_record();
    }

    fn apply(&mut self, batch: WriteBatch) {
        let v = self.log.add_record(batch.data());
        println!("{:?}", v);
    }
}
