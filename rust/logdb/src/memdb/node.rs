use memdb::fixed_list::FixedList;

pub type NodeId = usize;
pub type Key = Vec<u8>;

#[derive(Debug)]
pub struct Node {
    id: NodeId,
    key: Key,
    value: Vec<u8>,
    next: FixedList,
}

impl Node {
    pub fn new(id: NodeId, key: Key, value: Vec<u8>, next: FixedList) -> Node {
        Node {
            id,
            key,
            value,
            next,
        }
    }

    pub fn key(&self) -> &Key {
        &self.key
    }

    pub fn value(&self) -> String {
        String::from_utf8(self.value.clone()).unwrap()
    }

    pub fn id(&self) -> usize {
        self.id
    }

    pub fn get_next(&self, i: usize) -> Option<usize> {
        self.next.get(i)
    }

    pub fn height(&self) -> usize {
        self.next.height()
    }

    pub fn set_next(&self, pos: usize, v: usize) {
        self.next.set(pos, v);
    }
}

#[cfg(test)]
mod tests {
    use super::{Node, FixedList};

    #[test]
    fn test_access_node_attribute() {
        let key = "key";
        let value = "value";
        let height = 10;
        let nid = 0;
        let n = Node::new(
            nid,
            Vec::from(key),
            Vec::from(value),
            FixedList::new(height),
        );

        assert_eq!(n.key(), &Vec::from(key));

        let vv = value.to_string();
        assert_eq!(n.value(), vv);

        assert_eq!(n.id(), nid);

        assert_eq!(n.height(), height);
    }

    #[test]
    fn test_next_node() {
        let n = Node::new(0, Vec::from("key"), Vec::from("value"), FixedList::new(10));
        assert_eq!(n.get_next(1), None);
        n.set_next(1, 2);
        assert_eq!(n.get_next(1), Some(2));
    }
}
