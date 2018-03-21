use std::ptr;

#[derive(Debug, Clone, Copy)]
pub struct Version {
    value: u32,
}

impl Version {
    pub fn new(v: u32) -> Self {
        Self { value: v }
    }
}

type Link<T> = Box<Node<T>>;

#[derive(Debug)]
pub struct VersionSet {
    dummy: Link<Version>,
}

#[derive(Debug)]
pub struct Node<T> {
    v: T,
    next: *mut Node<Version>,
    prev: *mut Node<Version>,
}

impl<T> Node<T> {
    pub fn new(v: T) -> Self {
        Node {
            v: v,
            next: ptr::null_mut(),
            prev: ptr::null_mut(),
        }
    }
}

pub struct Iter<'a> {
    head: *const Node<Version>,
    next: &'a Node<Version>,
}

impl Drop for VersionSet {
    fn drop(&mut self) {
        let finish = self.dummy.as_ref() as *const _;
        let mut n = self.dummy.prev;

        while (n as *const _) != finish {
            unsafe {
                Box::from_raw(n); // take back the right of releasing
                n = (*n).prev;
            }
        }
    }
}

impl<'a> Iterator for Iter<'a> {
    type Item = &'a Version;

    fn next(&mut self) -> Option<Self::Item> {
        if (self.next as *const _) == self.head {
            None
        } else {
            let v = self.next;
            self.next = unsafe { &(*self.next.next) };
            Some(&v.v)
        }
    }
}

impl VersionSet {
    pub fn new() -> Self {
        let mut n = Box::new(Node::new(Version::new(0)));
        n.next = &mut *n;
        n.prev = &mut *n;

        VersionSet { dummy: n }
    }

    pub fn append(&mut self, n: Version) {
        let mut new_node = Box::new(Node::new(n));

        new_node.prev = self.dummy.prev;
        new_node.next = &mut *self.dummy;

        unsafe {
            (*new_node.prev).next = &mut *new_node;
            // Take over the right of releaseing new_node
            self.dummy.prev = Box::into_raw(new_node);
        };
    }

    pub fn current(&self) -> Option<Version> {
        let r = self.dummy.prev;
        Some(unsafe { (*r).v })
    }

    pub fn iter(&self) -> Iter {
        let r = self.dummy.as_ref();
        let v = unsafe { self.dummy.next.as_ref().expect("failed to unwrap") };
        Iter { head: r, next: &v }
    }
}

pub fn main() {
    let mut v = VersionSet::new();

    let v1 = Version::new(0);
    let v2 = Version::new(1);
    let v3 = Version::new(2);
    let v4 = Version::new(3);
    let v5 = Version::new(4);
    let v6 = Version::new(5);

    v.append(v1);
    v.append(v2);
    v.append(v3);
    v.append(v4);
    v.append(v5);
    v.append(v6);

    for i in v.iter() {
        println!("{:?}", i);
    }

    // println!("{:?}", i.next());
}
