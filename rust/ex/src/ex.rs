use std::path::Path;
use options::Options;
use file::File;

pub struct Ex {
    pub options: Options
}

impl Ex {
    pub fn run(&self, mut paths: Vec<String>) {
        let mut files: Vec<File> = Vec::new();
        let mut dirs: Vec<File> = Vec::new();

        if paths.is_empty() {
            paths.push(".".to_owned());
        }

        for path in paths.iter() {
            match File::from_path(&Path::new(&path)) {
                Err(e) => {
                    println!("{} {}", path, e)
                },
                Ok(f) => {
                    if f.is_dirctory() {
                        dirs.push(f);
                    } else {
                        files.push(f);
                    }
                }
            }
        }
    }

    fn print_files(&self) {
    }

    fn print_dirs(&self) {
    }

    fn print(&self) {
        print_files();
        print_dirs();
    }
}
