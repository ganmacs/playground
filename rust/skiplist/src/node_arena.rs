use fixed_list::FixedList;
use node::{Node, Key, NodeId};
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

#[cfg(test)]
mod tests {
    use super::NodeArena;

    #[test]
    fn test_node_arena() {
        let mut na = NodeArena::new();

        assert!(na.get(1).is_none());
        let nid = na.allocate_node(Vec::from("key"), Vec::from("value"), 10);
        let node = na.get(nid).unwrap();
        assert_eq!(node.key(), &Vec::from("key"));
        assert_eq!(node.value(), String::from("value"));
    }

    #[test]
    fn test_node_arena_nead() {
        let na = NodeArena::new();

        let head = na.head();
        assert!(na.is_head(head));
        assert_eq!(na.head().id(), na.get(0).unwrap().id());
    }
}
