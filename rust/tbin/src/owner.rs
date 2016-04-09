fn eat_box(boxed_int: Box<i32>) {
    println!("{:?}", boxed_int);
}

fn borrow_box(borrow_int: &i32) {
    println!("{:?}", borrow_int);
}

struct Foo { x: i32 }

fn c_c(x: char) {
    println!("{:?}", x);
}

fn main() {
    let i_box = Box::new(12);
    println!("imuutable {:?}", i_box);

    let mut m_box = i_box;
    println!("mutable {:?}", m_box);
    *m_box = 3;

    println!("{:?}", m_box);

    let boxed_int = Box::new(5);
    borrow_box(&boxed_int);
    borrow_box(&boxed_int);
    // eat_box(&boxed_int);

    // let mut m_int = 10;

    // {
    //     let i_int = &m_int;
    //     m_int = 10;
    // }

    let mut aaa = Foo { x: 10 };

    {
        let bbb = &mut aaa;
        bbb.x = 11;
        let k = bbb.x;

        println!("{:?}", k);
        println!("{}", bbb.x);
    }


    let a = 'a';
    let b = &a;
    c_c(*b);
    println!("{}", b);
}
