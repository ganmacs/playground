pub struct VersionSet {
    dbname: String,
    file_number: u64,
}

impl VersionSet {
    pub fn new(dbname: &str) -> Self {
        VersionSet {
            dbname: dbname.to_owned(),
            file_number: 1,
        }
    }

    pub fn next_file_num(&mut self) -> u64 {
        self.file_number += 1;
        self.file_number
    }
}

pub struct Version {
    file_number: u64,
}

impl Version {
    pub fn new() -> Self {
        Version { file_number: 0 }
    }


    pub fn file_num(&self) -> u64 {
        self.file_number
    }
}
