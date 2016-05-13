use std::fs;
use std::io::Result as IOResult;
use std::path::{Path, PathBuf};

pub struct File {
    pub name: String,
    pub metadata: fs::Metadata,
    pub path: PathBuf
}

impl File {
    pub fn from_path(path: &Path) -> IOResult<File> {
        fs::symlink_metadata(path).map(|metadata| File::with_metadata(metadata, path))
    }

    pub fn with_metadata(metadata: fs::Metadata, path: &Path) -> File {
        let filename = match path.file_name() {
            Some(name) => name.to_string_lossy().to_string(),
            None => String::new()
        };

        File {
            name: filename,
            path: path.to_path_buf(),
            metadata: metadata
        }
    }

    pub fn is_dirctory(&self) -> bool {
        self.metadata.is_dir()
    }
}
