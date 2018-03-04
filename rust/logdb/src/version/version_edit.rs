use ikey::InternalKey2;

pub struct FileMetaDataBuilder {
    file_num: Option<u64>,
    size: Option<u64>,
    largest: Option<InternalKey2>,
    smallest: Option<InternalKey2>,
}

impl FileMetaDataBuilder {
    pub fn new() -> Self {
        FileMetaDataBuilder {
            file_num: None,
            size: None,
            largest: None,
            smallest: None,
        }
    }

    pub fn file_num(&mut self, num: u64) -> &Self {
        self.file_num = Some(num);
        self
    }

    pub fn size(&mut self, size: u64) -> &Self {
        self.size = Some(size);
        self
    }

    pub fn largest(&mut self, largest: InternalKey2) -> &Self {
        self.largest = Some(largest);
        self
    }

    pub fn smallest(&mut self, smallest: InternalKey2) -> &Self {
        self.smallest = Some(smallest);
        self
    }

    pub fn build(self) -> FileMetaData {
        if self.file_num.is_none() {
            panic!("file num must be set")
        }

        if self.size.is_none() {
            panic!("size must be set")
        }

        if self.largest.is_none() {
            panic!("largest must be set")
        }

        if self.smallest.is_none() {
            panic!("smallest must be set")
        }

        FileMetaData {
            file_num: self.file_num.unwrap(),
            size: self.size.unwrap(),
            largest: self.largest.unwrap(),
            smallest: self.smallest.unwrap(),
        }
    }
}


pub struct FileMetaData {
    file_num: u64,
    size: u64,
    largest: InternalKey2,
    smallest: InternalKey2,
}

// impl FileMetaData {
//     pub fn new(num: u64) -> Self {
//         FileMetaData {
//             file_num: num,
//             size: 0,
//         }
//     }
// }

pub struct VersionEdit {
    inner: Vec<(FileMetaData, usize)>,
}

impl VersionEdit {
    pub fn new() -> Self {
        VersionEdit { inner: vec![] }
    }

    pub fn add_file(&mut self, meta: FileMetaData, level: usize) {
        self.inner.push((meta, level));
    }
}
