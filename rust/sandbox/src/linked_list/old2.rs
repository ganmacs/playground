pub struct List<T> {
    head: Link<T>,
}

type Link<T> = Option<Box<Node<T>>>;

struct Node<T> {
    elem: T,
    next: Link<T>,
}


impl<T> List<T> {
    pub fn new() -> Self {
        Self { head: None }
    }

    pub fn push(&mut self, elem: T) {
        let mut new_node = Box::new(Node {
            elem: elem,
            next: None,
        });

        match self.head.take() {
            Some(v) => new_node.next = Some(v),
            None => (),
        }

        self.head = Some(new_node);
    }

    pub fn pop(&mut self) -> Option<T> {
        match self.head.take() {
            Some(old) => {
                let v = *old;
                self.head = v.next;
                Some(v.elem)
            }
            None => None,
        }
    }
}



pub fn main() {
    let mut v = List::new();
    v.push(1);
    v.push(2);
    v.push(3);


    println!("{:?}", v.pop());
    println!("{:?}", v.pop());
    println!("{:?}", v.pop());


}
