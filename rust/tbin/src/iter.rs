truct Fibonacci {
    curr: u32,
    next: u32,
}

impl Iterator for Fibonacci {
    type Item = u32;

    fn next(&mut self) -> Option<u32> {
        let new = self.curr + self.next;
        self.curr = self.next;
        self.next = new;
        Some(self.curr)
    }
}

fn fibonacci() -> Fibonacci {
    Fibonacci { curr: 1, next: 1 }
}

fn main() {
    for i in fibonacci().take(5) {
        println!("{:?}", i);
    }
    let apple = Some(1);
    let f: Option<i32> = None;
    let a = apple.map(|a| 1 + a);
    let b = f.map(|a| a+1 );
    println!("{:?}", apple);
    println!("{:?}", a);
    setup();
}
