mod node_arena;
mod node;
mod fixed_list;
mod skiplist;

const MAX_HEIGHT: usize = 12;

pub type MemDB = skiplist::SkipList;
