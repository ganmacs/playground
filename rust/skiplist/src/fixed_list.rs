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

    pub fn set(&self, pos: usize, v: usize) -> bool {
        if pos < self.height {
            self.list[pos].set(Some(v));
            true
        } else {
            false
        }
    }

    pub fn get(&self, i: usize) -> Option<NodeId> {
        self.list.get(i).and_then(|v| v.get())
    }

    pub fn height(&self) -> usize {
        self.height
    }
}

#[cfg(test)]
mod tests {
    use super::FixedList;

    #[test]
    fn test_fixed_list() {
        let list = FixedList::new(10);
        let nid = 10;
        assert_eq!(list.height, 10);

        assert_eq!(list.get(1), None);
        list.set(1, nid);

        assert_eq!(list.get(1), Some(nid));
    }

    #[test]
    fn test_when_out_of_bound_of_height() {
        let list = FixedList::new(1);

        assert!(!list.set(100, 10));
        assert_eq!(list.get(100), None);
    }
}
