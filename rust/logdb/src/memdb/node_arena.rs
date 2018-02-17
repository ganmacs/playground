use memdb::fixed_list::FixedList;
use memdb::node::{Node, Key, NodeId};
use super::MAX_HEIGHT;

#[derive(Debug)]
pub struct NodeArena {
    nodes: Vec<Node>,
    head: NodeId,
}

impl NodeArena {
    pub fn new() -> Self {
        let mut arena = NodeArena {
            nodes: vec![],
            head: 0,
        };
        arena.allocate_node(vec![], vec![], MAX_HEIGHT);
        arena
    }

    pub fn is_head(&self, node: &Node) -> bool {
        &self.head == &node.id()
    }

    pub fn head(&self) -> &Node {
        self.get(self.head).unwrap()
    }

    pub fn allocate_node(&mut self, key: Key, value: Vec<u8>, height: usize) -> NodeId {
        let id = self.nodes.len();
        let next = FixedList::new(height);
        let n = Node::new(id, key, value, next);
        self.nodes.push(n);
        id
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
                    self.head().set_next(i, node.id());
                }

            }
        }
    }

    pub fn get(&self, id: NodeId) -> Option<&Node> {
        self.nodes.get(id)
    }
}
