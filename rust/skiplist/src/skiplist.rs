use rand;
use rand::Rng;
use std::usize;
use node::{Node, Key};
use fixed_list::FixedList;
use node_arena::NodeArena;
use super::MAX_HEIGHT;

#[derive(Debug)]
pub struct SkipList {
    arena: NodeArena,
}

impl SkipList {
    pub fn new() -> Self {
        SkipList { arena: NodeArena::new() }
    }

    pub fn get(&self, key: &Key) -> Option<String> {
        self.find_greater_than_eq(&key).and_then(
            |v| if v.key() == key {
                Some(v.value())
            } else {
                None
            },
        )
    }

    pub fn insert(&mut self, key: Key, value: Vec<u8>) -> bool {
        let mut f = FixedList::new(MAX_HEIGHT);
        if let Some(n) = self.find_greater_than_eq_and_set_prev(&key, &mut f) {
            if n.key() == &key {
                // already exist
                return false;
            }
        }
        let height = rand::thread_rng().gen_range(1, MAX_HEIGHT);
        let id = self.arena.allocate_node(key, value, height);
        self.arena.update(id, f);
        true
    }

    fn find_greater_than_eq_and_set_prev(&self, key: &Key, prev: &mut FixedList) -> Option<&Node> {
        let mut level = (MAX_HEIGHT as i8) - 1;
        let mut node = self.arena.head();

        loop {
            let next_node_i = node.get_next(level as usize);
            if let Some(next) = next_node_i.and_then(|i| self.arena.get(i)) {
                if next.key() < key {
                    node = next;
                } else {
                    if !self.arena.is_head(&node) {
                        prev.set(level as usize, node.id());
                    }

                    level -= 1;
                    if level < 0 {
                        return Some(next);
                    }
                }
            } else {
                if !self.arena.is_head(&node) {
                    prev.set(level as usize, node.id());
                }
                level -= 1;
                if level < 0 {
                    return None;
                }
            }
        }
    }

    fn find_greater_than_eq(&self, key: &Key) -> Option<&Node> {
        let mut level = (MAX_HEIGHT as i8) - 1;
        let mut node = self.arena.head();

        loop {
            let next_node_id = node.get_next(level as usize);
            if let Some(next) = next_node_id.and_then(|i| self.arena.get(i)) {
                if next.key() < key {
                    node = next;
                } else {
                    level -= 1;
                    if level < 0 {
                        return Some(next);
                    }
                }
            } else {
                level -= 1;
                if level < 0 {
                    return None;
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::SkipList;

    #[test]
    fn test_skiplist() {
        let mut list = SkipList::new();
        let hash = vec![
            ("key", "value"),
            ("key1", "value1"),
            ("key2", "value2"),
            ("key3", "value3"),
            ("key4", "value4"),
            ("key5", "value5"),
        ];

        for v in hash {
            list.insert(Vec::from(v.0), Vec::from(v.1));
            assert_eq!(list.get(&Vec::from(v.0)), Some(String::from(v.1)));
        }

        assert_eq!(list.get(&Vec::from("invalid")), None);
    }
}
