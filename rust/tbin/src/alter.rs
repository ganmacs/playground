use std::collections::HashMap;

#[derive(PartialEq, Eq, Hash)]
struct Account<'a> {
    username: &'a str,
    password: &'a str,
}

struct AccountInfo<'a> {
    name: &'a str,
    email: &'a str,
}

type Accounts<'a> = HashMap<Account<'a>, AccountInfo<'a>>;

fn main() {
    let mut accounts: Accounts = HashMap::new();
    let account = Account {
        username: "foo",
        password: "pass",
    };

    let account_info = AccountInfo {
        name: "foo bar",
        email: "aaa@email.com"
    };

    accounts.insert(account,  account_info);
    println!("{:?}", accounts);
}
