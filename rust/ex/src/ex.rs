use std::path::Path;
use std::process;

use dir::Dir;
use file::File;
use config::Config;

pub struct Ex {
    config: Config,
}

impl Ex {
    pub fn new() -> Self {
        Ex {
            config: Config::with_args()
        }
    }

    pub fn run(&self)  {
        match self.collect() {
            Ok((dir, files)) => self.pretty_print(dir, files),
            Err(e) => println!("{:?}", e)
        }
    }

    fn collect(&mut self) -> Result<(Vec<Dir>, Vec<File>), String> {
        let mut files: Vec<File> = Vec::new();
        let mut dirs: Vec<Dir> = Vec::new();

        if self.paths.is_empty() {
            self.paths.push(".".to_owned());
        }

        for path in self.paths.iter() {
            match File::from_path(&Path::new(&path)) {
                Err(e) => {
                    println!("{}: {}", path, e);
                },
                Ok(f) => {
                    if f.is_dirctory() {
                        match f.to_dir() {
                            Ok(d) => dirs.push(d),
                            Err(e) => println!("{}: {}", path, e)
                        }
                    } else {
                        files.push(f);
                    }
                }
            }
        }
        Ok((dirs, files))
    }

    fn pretty_print(&self, dirs: Vec<Dir>, files: Vec<File>) {
    }
}
