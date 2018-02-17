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
        self.next.set(pos, v)
    }
}
