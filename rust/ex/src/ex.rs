use std::path::Path;
use options::Options;
use dir::Dir;
use file::File;

pub struct Ex {
    pub options: Options
}


impl Ex {
    pub fn exec(&self, paths: Vec<String>)  {
        match self.collect(paths) {
            Ok((dir, files)) => self.pretty_print(dir, files),
            Err(e) => println!("{:?}", e)
        }
    }

    fn pretty_print(&self, dirs: Vec<Dir>, files: Vec<File>) {
    }

    fn collect(&self, mut paths: Vec<String>) -> Result<(Vec<Dir>, Vec<File>), String> {
        let mut files: Vec<File> = Vec::new();
        let mut dirs: Vec<Dir> = Vec::new();

        if paths.is_empty() {
            paths.push(".".to_owned());
        }

        for path in paths.iter() {
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
}
