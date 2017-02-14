use std::rc::Rc;

#[derive(Debug)]
struct Nil(u32);

impl Nil {
    fn hey(&self) -> Nil {
        self.clone()
    }

    fn foo(&mut self) -> Nil {
        Nil(self.0 + 1)
    }
}

impl Clone for Nil {
    fn clone(&self) -> Nil {
        Nil(self.0 + 1)
    }
}

impl Drop for Nil {
    fn drop(&mut self) -> () {
        println!("tanomu!!! {:?}", self)
    }
}

fn muta(v: &mut Nil) {
    println!("muta {:?}", v);
}

#[derive(Debug)]
struct V(Vec<u32>);

impl Drop for V {
    fn drop(&mut self) -> () {
        println!("good bye V!!! {:?}", self)
    }
}

impl V {
    fn hello(&self) -> Vec<u32> {
        let k = vec![10];
        // k.split_off(2);

        let v = &self.0;
        let v2 = self.clone();

        k
        // let v3 = v2.0.split_off(1);
        // v3
    }
}

fn a1(v: Nil) {
    println!("{:?}", v);
}

fn a2(v: &Nil) {
    println!("{:?}", v);
}

fn main() {

    {
        let v = V(vec![1]);
        v.hello();
        println!("{:?}", v);

    }

    println!("------------ref--------------");
    {
        // v: Nil
        let v = Nil(10);
        a2(&v);
        v.hey();
        a1(v);

        // v: &Node
        let ref v = Nil(10);
        a2(v);
        v.hey();
        a1(v.clone());

        // v: &&Node
        let ref v = &Nil(10);
        a2(v);
        v.hey();
        a1(v.clone().clone());

        let mut v = Nil(10);
        println!("{:?}", v);
        v = Nil(20);
        println!("{:?}", v);

    }

    println!("-------------ref mut----------------");

    {
        let mut v = Nil(10);
        v = Nil(15);
        v.foo();

        let mut v = &mut Nil(20);
        // raise an error
        // v = &mut Nil(25);
        //          ^ temporary value dropped here while still borrowed
        v.foo();

        let ref mut v = Nil(30);
        // raise errors
        // v = &mut Nil(35);
        //          ^ temporary value dropped here while still borrowed
        // ^ reassignment
        v.foo();

        let ref mut v = &mut Nil(30);
        // raise errors
        // v = Nil(35);
        // expected type `&mut &mut Nil`
        v.foo();
    }

    println!("-------------------------------");

    {
        let nil = Nil(1);
        let v = nil.clone();
        let k = v.hey();
    }

    println!("-------------------------------");
    let mut nil = Nil(1);
    {
        {
            let v = &nil;
        }
        muta(&mut nil);

    }

    println!("-------------------------------");
    {
        let v = Nil(1);
        let v1 = &v;
        // let v2 = *v1;
        // println!("{:?}", v2);
    }

    println!("-------------------------------");
    {
    }

    println!("{:?}", "done");
}
