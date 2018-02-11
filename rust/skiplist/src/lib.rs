extern crate rand;

mod node_arena;
mod node;
mod fixed_list;

use rand::Rng;
use std::usize;
use node::{Node, Key};
use fixed_list::FixedList;
use node_arena::NodeArena;

const MAX_HEIGHT: usize = 12;

#[derive(Debug)]
pub struct SkipList {
    arena: NodeArena,
}

pub fn new() -> SkipList {
    SkipList::new()
}

impl SkipList {
    fn new() -> Self {
        SkipList { arena: NodeArena::new() }
    }

    pub fn get(&mut self, key: &Key) -> Option<&Node> {
        self.find_greater_than_eq(&key).and_then(
            |v| if v.key() == key {
                Some(v)
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
