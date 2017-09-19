pub fn run() {
    let mut v = 1;

    {
        let mut f = |k| {
            println!("{:?}", v);
            v += k;
            println!("{:?}", v);
        };
        f(1);
    }


    println!("{:?}", v);

    let fn_fact = factory();
    println!("fooo {:?}", fn_fact(1));

    println!("{:?}", call_with_ref(|i| i + 1));
    println!("{:?}", call_with_ref2(|&i| i + 1));
    println!("{:?}", call_with_ref3(|i| i + 1));

    println!("-------------------------------");

    let mut val = 1;
    {
        let mut func = move |k: i32| val = val + k;
        func(10);

        println!("{:?}", val);
        foo(&mut val)
    }
    println!("{:?}", val);
}

fn foo(x: &mut i32) {
    *x += 1;
}


fn factory() -> Box<Fn(i32) -> i32> {
    let num = 5;
    Box::new(move |v| v + num)
}


fn call_with_ref<F>(sc: F) -> i32
    where F: Fn(i32) -> i32
{
    sc(10)
}


fn call_with_ref2<F>(sc: F) -> i32
    where F: Fn(&i32) -> i32
{
    sc(&10)
}

fn call_with_ref3<F>(sc: F) -> i32
    where F: for<'a> Fn(&'a i32) -> i32
{
    let v = 10;
    sc(&v)
}
