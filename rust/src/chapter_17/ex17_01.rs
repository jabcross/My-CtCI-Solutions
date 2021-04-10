// 17.1 Add Without Plus

fn add_without_plus(a: i32, b: i32) -> i32 {
    if b == 0 {
        return a;
    }
    add_without_plus(a ^ b, (a & b) << 1)
}

#[test]
fn test() {
    for (a, b) in &[(1, 1), (13, 12), (10, -1)] {
        assert!(add_without_plus(*a, *b) == a + b);
    }

    println!("Ex 17.1 ok!");
}
