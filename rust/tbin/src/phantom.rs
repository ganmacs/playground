use std::ops::Add;
use std::marker::PhantomData;

#[derive(Debug, Clone, Copy)]
enum Inch{}

#[derive(Debug, Clone, Copy)]
enum Mm{}

#[derive(Debug, Clone, Copy)]
struct Length<Unit>(f64, PhantomData<Unit>);

impl<Unit> Add for Length<Unit> {
    type Output = Length<Unit>;

    fn add(self, rhs: Length<Unit>) -> Length<Unit> {
        Length(self.0 + rhs.0, PhantomData)
    }
}


fn main() {
    let one_foot: Length<Inch> = Length(12.0, PhantomData);
    let t = one_foot + one_foot;
    println!("{:?}", t);
}
