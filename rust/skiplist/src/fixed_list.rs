use std::cell::Cell;
use node::NodeId;

#[derive(Debug)]
pub struct FixedList {
    height: usize,
    list: Vec<Cell<Option<NodeId>>>,
}

impl FixedList {
    pub fn new(height: usize) -> Self {
        let mut list = Vec::with_capacity(height);
        for _ in 0..height {
            list.push(Cell::new(None))
        }
        FixedList { height, list }
    }

    pub fn set(&self, pos: usize, v: usize) {
        if pos < self.height {
            self.list[pos].set(Some(v))
        }
    }

    pub fn get(&self, i: usize) -> Option<NodeId> {
        self.list.get(i).and_then(|v| v.get())
    }

    pub fn into_iter(self) -> Vec<Option<NodeId>> {
        self.list.iter().map(|v| v.get()).collect()
    }

    pub fn height(&self) -> usize {
        self.height
    }
}
