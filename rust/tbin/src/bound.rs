#[derive(Debug)]
struct Foo;
#[derive(Debug)]
struct Bar;
#[derive(Debug)]
struct Bal;

trait Red {}
trait Blue {}

impl Red for Foo {}
impl Red for Bal {}
impl Blue for Bar {}

fn red<T: Red>(_: &T) -> &'static str { "red" }
fn blue<T: Blue>(_: &T) -> &'static str { "blue" }

fn main() {
    let foo = Foo;
    let bar = Bar;
    let bal = Bal;

    println!("{:?}", red(&foo));
    println!("{:?}", red(&bal));
    println!("{:?}", blue(&bar));
}
