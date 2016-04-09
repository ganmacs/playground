use std::io;

fn main() {
    println!("Guess the number!");
    println!("Please input youur guess");

    let mut guess = String::new();
    io::stdin().read_line(&mut guess).expect("Fialed to read line");


    println!("You guessued: {}", guess);
}
