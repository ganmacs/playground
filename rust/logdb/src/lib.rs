extern crate bytes;
extern crate crc;
extern crate rand;
extern crate regex;
#[macro_use]
extern crate lazy_static;

mod log;
mod batch;
mod memdb;
mod ikey;
mod filename;
mod version;
mod table;

use batch::WriteBatch;
use bytes::Bytes;
use log::{LogReader, LogWriter};
use memdb::MemDB;
use ikey::InternalKey;
use std::fs;
use std::io::{BufWriter, BufReader};
use std::fs::File;
use std::path::Path;
use std::str;
use filename::FileType;
use version::{VersionSet, VersionEdit};
use table::TableBuilder;
use memdb::MemDBIterator;

pub struct LogDB {
    log: LogWriter<BufWriter<File>>,
    dbname: String,
    versions: VersionSet,
    mem: MemDB,
    imm: Option<MemDB>,
}

pub fn open(dir: &str) -> LogDB {
    let mut db = LogDB::new(dir);
    let mut edit = VersionEdit::new();
    db.recover(&mut edit);
    db
}

impl LogDB {
    fn new(dir: &str) -> Self {
        if !Path::new(&dir).exists() {
            fs::create_dir(&dir).unwrap()
        }

        let mut v = VersionSet::new(dir);
        let fname = FileType::LOG(dir, v.next_file_num()).filename();
        let fd = fs::OpenOptions::new() // add read permission?
            .write(true)
            .create(true)
            .open(fname)
            .unwrap();
        let writer = BufWriter::new(fd);
        LogDB {
            dbname: dir.to_owned(),
            log: LogWriter::new(writer),
            versions: v,
            mem: MemDB::new(),
            imm: None,
        }
    }

    pub fn get(&self, key: &str) -> Option<Bytes> {
        let ikey = InternalKey::new(key, 0); // XXX use actual seq
        self.mem.get(&ikey).or_else(|| {
            self.imm.as_ref().and_then(|v| v.get(&ikey))
        })
    }

    pub fn set(&mut self, key: &str, value: &str) {
        let mut b = WriteBatch::new();
        b.put(key, value);
        self.apply(b)
    }

    fn recover(&mut self, edit: &mut VersionEdit) {
        let current = FileType::CURRENT(&self.dbname).filename();
        if !Path::new(&current).exists() {
            // TODO create current file when create db
            println!("CURRENT file does not exist");
        }

        let paths = fs::read_dir(&self.dbname).unwrap();
        for p in paths {
            let path = &p.unwrap().path();
            let ft = FileType::parse_name(path.to_str().unwrap());
            if ft.is_logfile() {
                self.replay_logfile(path, edit);
            }
        }
    }

    fn replay_logfile(&mut self, path: &std::path::PathBuf, edit: &mut VersionEdit) {
        let reader = BufReader::new(fs::File::open(path).unwrap());
        let mut lr = LogReader::new(reader);
        let record = lr.read_record().unwrap();
        if record.len() == 0 {
            println!("skip");
            return;
        }

        let mut mem = MemDB::new();
        let write_batch = WriteBatch::load_data(record);
        for (key_kind, ukey, value) in write_batch.into_iter() {
            mem.add(key_kind, &ukey, &value);
            // TODO: memory usage is larger than buffer size
        }

        self.write_level0_table(edit, &mut mem.into_iter())
    }

    fn write_level0_table(&mut self, edit: &mut VersionEdit, mem: &mut MemDBIterator) {
        let num = self.versions.next_file_num();
        let meta = TableBuilder::build(&self.dbname, mem, num);

        // XXX
        edit.add_file(meta, 0);
    }

    fn apply(&mut self, batch: WriteBatch) {
        self.log.add_record(batch.data());

        for (key_kind, ukey, value) in batch.into_iter() {
            self.mem.add(key_kind, &ukey, &value);
        }
    }
}
