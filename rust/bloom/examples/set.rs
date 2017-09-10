extern crate bloom;

use bloom::Bloom;

fn main() {
    let mut filter = Bloom::new(1000, 10);
    let key0 = "key0";
    let key1 = "key1";
    let key2 = "key2";
    let key3 = "key3";
    let key4 = "key4";
    let key5 = "key5";
    let key6 = "key6";
    let key7 = "key7";
    let key8 = "key8";
    let key9 = "key9";

    assert!(!filter.check(&key0));
    assert!(!filter.check(&key1));
    assert!(!filter.check(&key2));
    assert!(!filter.check(&key3));
    assert!(!filter.check(&key4));
    assert!(!filter.check(&key5));
    assert!(!filter.check(&key6));
    assert!(!filter.check(&key7));
    assert!(!filter.check(&key8));
    assert!(!filter.check(&key9));

    filter.set(&key0);
    filter.set(&key1);
    filter.set(&key2);
    filter.set(&key3);
    filter.set(&key4);
    filter.set(&key5);
    filter.set(&key6);
    filter.set(&key7);
    filter.set(&key8);
    filter.set(&key9);

    assert!(filter.check(&key0), true);
    assert!(filter.check(&key1), true);
    assert!(filter.check(&key2), true);
    assert!(filter.check(&key3), true);
    assert!(filter.check(&key4), true);
    assert!(filter.check(&key5), true);
    assert!(filter.check(&key6), true);
    assert!(filter.check(&key7), true);
    assert!(filter.check(&key8), true);
    assert!(filter.check(&key9), true);
}
