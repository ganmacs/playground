use std::iter::Peekable;
use std::str::Chars;

#[derive(Debug)]

enum Node {
    Cell { car: Box<Node>, cdr: Box<Node> },
    Int { v: i32 },
    Fn { name: &'static str },
    Dot,
    RParen,
    Nil,
}

#[derive(Debug)]
enum ParseError {
    InvalidSyntax,
    UnmatchedParen
}

type ParseResult = Result<Node, ParseError>;

fn parse_list(input: &mut Peekable<Chars>) -> ParseResult {
    let v = try!(parse(input));

    match v {
        Node::Nil => return Err(ParseError::UnmatchedParen),
        Node::Dot => return Err(ParseError::UnmatchedParen),
        Node::RParen => return Ok(Node::Nil),
        _ => ()
    };

    let k = try!(parse_list(input));

    Ok(Node::Cell {
        car: Box::new(v),
        cdr: Box::new(k)
    })
}

fn number(n: u32, input: &mut Peekable<Chars>) -> Node {
    let mut v = n;
    if let Some(x) = input.peek() {
        if x.is_digit(10) {
            v = v * 10 + x.to_digit(10).unwrap();
        }
    }
    Node::Int { v: v as i32 }
}

fn parse_digit(c: char, input: &mut Peekable<Chars>) ->  ParseResult {
    Ok(number(c.to_digit(10).unwrap(), input))
}

fn parse(input: &mut Peekable<Chars>) ->  ParseResult {
    match input.next() {
        None => Ok(Node::Nil),
        Some(c) =>
            match c {
                '(' => {
                    if Some(&')') == input.peek() {
                        return Ok(Node::Nil);
                    }
                    parse_list(input)
                },
                ' ' => parse(input),
                ')' => Ok(Node::RParen),
                '+' => Ok(Node::Fn { name: "+" }),
                x if x.is_digit(10) => parse_digit(x, input),
                _ => {
                    Err(ParseError::InvalidSyntax)
                }
            }
    }
}
fn prim_add(ast: Node) -> i32 {
    match ast {
        Node::Cell { car: x,  cdr: y } => {
            if let Node::Int{ v: k } = *x {
                k + prim_add(*y)
            } else {
                0
            }
        },
        _ => 0
    }
}

fn eval(ast: Node) -> Result<Node, &'static str> {    // specific type
    match ast {
        Node::Cell { car: x,  cdr: y } => {
            let fun = eval(*x);
            match try!(fun) {
                Node::Fn { name: n } => {
                    if n == "+" { Ok(Node::Int{ v: prim_add(*y)}) } else { Err("erro") }
                },
                _ => Err("others")
            }
        },
        x => Ok(x)
    }
}

fn lprint(result: Node) {
    match result {
        Node::Int { v: v } => println!("{}", v),
        x => println!("{:?}", x)
    }
}

fn main() {
    let input: &str = "(+ 1 2)";
    match parse(&mut input.chars().peekable())  {
        Ok(ast) => {
            println!("{:?}", ast);
            match eval(ast) {
                Ok(result) => lprint(result),
                Err(v) => println!("{:?}", v)
            }
        },
        Err(v) => println!("{:?}", v)
    };
}
