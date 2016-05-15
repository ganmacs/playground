use std::io::Result as IOResult;
use std::path::{PathBuf, Path};
use std::fs;

pub struct Dir {
    contents: Vec<PathBuf>,

    path: PathBuf
}


impl Dir {
    pub fn read(path: &Path) -> IOResult<Dir> {
        let entries = try!(fs::read_dir(path));
        let contents = try!(entries.map(|e| e.map( |e| e.path() )).collect());

        Ok(Dir {
            contents: contents,
            path: path.to_path_buf()
        })
    }
}
