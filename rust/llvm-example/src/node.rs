pub enum Node {
    Aref(String),
    Assgn(String, Box<Node>),
    Int(u64),
    Add(Box<Node>, Box<Node>),
    If(Box<Node>, Box<Node>, Box<Node>),
}

pub fn ifexpr(c: Node, t: Node, f: Node) -> Node {
    Node::If(Box::new(c), Box::new(t), Box::new(f))
}

pub fn aref<T: Into<String>>(str: T) -> Node {
    Node::Aref(str.into())
}

pub fn assgn<T: Into<String>>(k: T, v: Node) -> Node {
    Node::Assgn(k.into(), Box::new(v))
}

pub fn add(l: Node, r: Node) -> Node {
    Node::Add(Box::new(l), Box::new(r))
}

pub fn iint(v: u64) -> Node {
    Node::Int(v)
}
