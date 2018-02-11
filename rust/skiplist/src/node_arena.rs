use rand;
use rand::Rng;

use fixed_list::FixedList;
use node::{Node, Key, NodeId};

pub const MAX_HEIGHT: usize = 12;


#[derive(Debug)]
pub struct NodeArena {
    nodes: Vec<Node>,
}

impl NodeArena {
    pub fn new() -> Self {
        NodeArena { nodes: vec![] }
    }

    pub fn allocate_with_size(&mut self, key: Key, value: Vec<u8>, height: usize) -> NodeId {
        let id = self.nodes.len();
        let next = FixedList::new(height);
        let n = Node::new(id, key, value, next);
        self.nodes.push(n);
        id
    }

    pub fn allocate_node(&mut self, key: Key, value: Vec<u8>) -> NodeId {
        let height = rand::thread_rng().gen_range(1, MAX_HEIGHT);
        self.allocate_with_size(key, value, height)
    }

    pub fn update(&mut self, id: NodeId, prev: FixedList) {
        if let Some(node) = self.nodes.get(id) {
            let h = node.height();
            for i in 0..h {
                if let Some(p_node) = prev.get(i).and_then(|id| self.nodes.get(id)) {
                    p_node.get_next(i).map(|prev_next_node_id| {
                        node.set_next(i, prev_next_node_id)
                    });
                    p_node.set_next(i, node.id());
                } else {
                    // head FIX
                    self.nodes.get(0).map(|head| head.set_next(i, node.id()));
                }

            }
        }
    }

    pub fn get(&self, id: NodeId) -> Option<&Node> {
        self.nodes.get(id)
    }
}
