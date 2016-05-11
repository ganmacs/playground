use options::Options;
use std::path::Path;

pub struct Ex {
    pub options: Options
}

impl Ex {
    pub fn run(&self, mut paths: Vec<String>) {
        if paths.is_empty() {
            paths.push(".".to_owned());
        }

        for path in paths.iter() {
            println!("{:?}", Path::new(&path))
        }
    }
}
