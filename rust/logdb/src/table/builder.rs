use super::TableWriter;
use memdb::MemDBIterator;
use std::io::BufWriter;
use version::{FileMetaDataBuilder, FileMetaData};
use std::fs;
use filename::FileType;

pub struct TableBuilder {}


impl TableBuilder {
    pub fn build(dbname: &str, iterator: &mut MemDBIterator, num: u64) -> FileMetaData {
        let mut meta = FileMetaDataBuilder::new();
        meta.file_num(num);

        let fname = FileType::TABLE(dbname, num).filename();
        let fd = fs::OpenOptions::new() // add read permission?
            .write(true)
            .create(true)
            .open(fname)
            .unwrap();

        let bw = BufWriter::new(fd);
        let mut writer = TableWriter::new(bw);

        for (i, (k, v)) in iterator.enumerate() {
            if i == 0 {
                meta.smallest(k.clone());
            }

            writer.add(&k, &v);
            meta.largest(k); // must clone
        }


        meta.size(writer.size() as u64);
        meta.build()
    }
}
