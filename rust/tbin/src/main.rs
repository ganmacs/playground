// extern crate rary;

use std::fmt;
use std::fmt::Debug;
use std::boxed;
use deeply::nested::function as o_fun;
use std::marker::PhantomData;

mod my2;

mod deeply {
    pub mod nested {
        pub fn function() {
            println!("{}", "called deeply nested function");
        }
    }
}

struct Backend {
    name: &'static str
}

#[derive(Debug)]
enum Syntax {
    Statment(Box<Syntax>),
    Expr(Box<Syntax>),
    IntLit(i32),
    FloatLit(f32)
}
impl fmt::Display for Backend {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "name: {}", self.name)
    }
}

fn parse(s: Syntax) {
    match s {
        Syntax::Statment(v) => parse(*v),
        Syntax::Expr(v) => parse(*v),
        Syntax::IntLit(v) => println!("int literal {}", v),
        Syntax::FloatLit(v) => println!("float literal {}", v),
    }
}

fn p(v: & Vec<i32>) {
    println!("sa{}", v[0]);
}

fn f(v: &mut Vec<i32>) {
    (*v).push(10);
}

mod my {
    pub struct BlackBox<T> {
        pub contents: T,
    }

    impl<T> BlackBox<T> {
        pub fn new(contents: T) -> BlackBox<T> {
            BlackBox { contents: contents}
        }
    }
}

struct Val(f64);


impl Val {
    fn value(&self) -> &f64 { &self.0 }
}

struct Empty;
struct Null;

impl fmt::Display for Null {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "name: fxck")
    }
}

trait DoubleDrop<T> {
    fn double_drop(self, _: T);
}

impl<T: fmt::Display, U> DoubleDrop<T> for U {
    fn double_drop(self, x: T) {
        println!("{}", x);
    }
}

trait PrintInOption {
    fn print_in_option(self);
}

impl<T> PrintInOption for T where
    Option<T>: Debug {
    fn print_in_option(self) {
        println!("{:?}", Some(self));
    }
}

struct Container(i32, i32);

trait Contains {
    type A;
    type B;
    fn contains(&self, n1: &Self::A, n2: &Self::B) -> bool;
    fn first(&self) -> Self::A;
    // fn first(&self) -> i32;
    // fn last(&self) -> Self::B;
}

impl Contains for Container {
    type A = i32;
    type B = i32;

    fn contains(&self, n1: &i32, n2: &i32) -> bool {
        println!("{:?}", n1);
        (&self.0 == n1) && (&self.1 == n2)
    }
    fn first(&self) -> i32 { self.0 }
    // fn last(&self) -> i32 { &self.1; }
}

// fn diff<A, B, C>(container: &C) -> i32 where
//     C: Contains<A, B> {
//     let n1 = 1;
//     let n2 = 1;
//     // println!("{} {:?}",  n1, container.contains(&n1, &n2));
//     23;
// }

#[derive(PartialEq)]
struct PhantomTuple<A, B>(A, PhantomData<B>);

fn main() {
    let t1: PhantomTuple<char, f32> = PhantomTuple('Q', PhantomData);
    let t2: PhantomTuple<char, f64> = PhantomTuple('Q', PhantomData);
    println!("{:?}", t1 == t2);


    let n1 = 3;
    let n2 = 10;
    let c = Container(n1, n2);
    println!("{} {:?}",  n1, c.contains(&n1, &n2));
    println!("{:?}", c.first());

    let v = vec![1, 3, 3];
    v.print_in_option();

    let empty = Empty;
    let null = Null;
    empty.double_drop(null);
    "asdf".double_drop("asdf");

    my2::nested::myfunc();

    // rary::public_function();

    {
        use deeply::nested::function;
        function();
    }



    // o_fun();
    // let a = my::BlackBox { contents: "public information" };
    // let b = my::BlackBox::new("hogehgo");
    // println!("{}", a.contents);
    // println!("{}", b.contents);

    // let x = Val(3.0);
    // println!("{}", x.value());

    // let fnn = |i: i32| -> i32 { i + 1 };
    // let ifn = |i| i + 1;
    // println!("{}", fnn(10));
    // println!("{}", ifn(10));

    // let a = "asdf".to_owned();
    // println!("{:?}",a);

    // let y: &i32;
    // let x = 5;
    // println!("{}", x);
    // y = &x;

    // let mut v = 1;
    // {
    //     let y = &mut v;
    //     *y += 1;
    // }
    // println!("{}", v);


    // let a = vec![1,2,3];
    // let b = a;
    // println!("{:?}", b);
    // println!("{:?}", a);

    // let i = Syntax::IntLit(10);
    // let e = Syntax::Expr(Box::new(i));
    // parse(e);

    // let v = vec![1,2,3];
    // // let v2 = &v;
    // p(&v);

    // let mut v2 = vec![1,2,3];
    // f(&mut v2);
    // println!("{:?}", v2);

    // let k = 10;
    // {
    //     let b = k;
    //     println!("erro {}", k);
    //     println!("borrw1 {}", b);
    // }

    // println!("lender {}", k);


    // let a = Backend { name: "foobar" };
    // println!("Guess {}",a);
    // println!("{}", a.name);

    // let Backend { name: foo } = a;
    // println!("{}", foo);

}
