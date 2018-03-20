// use std::cell::Ref;
// use std::cell::RefCell;
// use std::rc::Rc;

// #[derive(Debug, Clone, Copy)]
// pub struct Version {
//     value: u64,
// }

// impl Version {
//     pub fn new(v: u64) -> Self {
//         Self { value: v }
//     }
// }

// #[derive(Debug)]
// pub struct A {
//     dummy: InnerLink<Version>,
// }

// type Link<T> = Option<InnerLink<T>>;

// type InnerLink<T> = Rc<RefCell<Node<T>>>;

// #[derive(Debug)]
// pub struct Node<T> {
//     v: T,
//     next: Link<T>,
//     prev: Link<T>,
// }

// impl<T> Node<T> {
//     pub fn new(v: T) -> InnerLink<T> {
//         Rc::new(RefCell::new(Node {
//             v: v,
//             prev: None,
//             next: None,
//         }))
//     }
// }

// impl A {
//     pub fn new() -> Self {
//         A { dummy: Node::new(Version::new(0)) }
//     }

//     pub fn append(&self, n: Version) {
//         let new_node: InnerLink<Version> = Node::new(n);

//         new_node.borrow_mut().prev = self.dummy.borrow().prev.clone();
//         new_node.borrow_mut().next = Some(self.dummy.clone());


//         self.dummy.borrow_mut().prev = Some(new_node.clone());
//         if let Some(dummy_prev) = self.dummy.borrow().prev.as_ref() {
//             dummy_prev.borrow_mut().next = Some(new_node.clone());
//         }
//     }

//     pub fn current(&self) -> Option<Ref<Version>> {
//         // let d = Rc::try_unwrap(self.dummy.clone()).expect("failed unwrap").into_inner();
//         // Rc::try_unwrap(self.dummy.clone()).expect("failed unwrap").into_inner();

//         // let d = self.dummy.borrow_mut().prev.take().unwrap();
//         // d.prev.take()

//         // Rc::try_unwrap(d).ok().unwrap().into_inner().v
//         // d.as_ref().map(
//         //     |v| Ref::map(v.borrow(), |node| &node.v),
//         // )
//     }
// }
