pub enum Node {
    Aref(String),
    Assgn(String, Box<Node>),
    Int(u64),
    Add(Box<Node>, Box<Node>),
    Sub(Box<Node>, Box<Node>),
    If(Box<Node>, Box<Node>, Box<Node>),
}

pub fn ifexpr(cond: Node, t_body: Node, e_body: Node) -> Node {
    Node::If(Box::new(cond), Box::new(t_body), Box::new(e_body))
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

pub fn sub(l: Node, r: Node) -> Node {
    Node::Sub(Box::new(l), Box::new(r))
}

pub fn iint(v: u64) -> Node {
    Node::Int(v)
}
