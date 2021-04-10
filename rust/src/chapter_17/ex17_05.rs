// 17.5 Letters and Numbers

// O(n) solution, O(n) extra space

/*
Finds longest subarray with same amount of letters and numbers.
Keeps a "balance" (number of letters and numbers for each prefix)
and keeps track of the leftmost and rightmost occurrences of each value.

Two positions with the same balance mark a subarray with the same amount of
letters and numbers.
*/

use std::collections::HashMap;

fn letters_numbers_longest_subarray(a: &[u8]) -> &[u8] {
    let mut balance = 0;
    let mut leftmost_with_balance_n = HashMap::new();
    let mut rightmost_with_balance_n = HashMap::new();

    // Starting balance is 0
    leftmost_with_balance_n.insert(0, -1);
    rightmost_with_balance_n.insert(0, -1);

    for i in 0..a.len() {
        match a[i] {
            b'a'..=b'z' => balance += 1,
            b'0'..=b'9' => balance -= 1,
            _ => panic!("Unknown character"),
        }
        rightmost_with_balance_n.insert(balance, i as i32);
        leftmost_with_balance_n.entry(balance).or_insert(i as i32);
    }

    if balance == 0 {
        // If balance == 0, the whole string is already balanced.
        return a;
    }

    let mut _max = (0, 0, 0);

    for (this_balance, &l) in leftmost_with_balance_n.iter() {
        let &r = rightmost_with_balance_n.get(this_balance).unwrap();
        _max = _max.max((r - l, (l + 1) as usize, (r + 1) as usize));
    }

    let (_, l, r) = _max;

    &a[l..r]
}

fn is_balanced(a: &[u8]) -> bool {
    let mut balance = 0;
    for i in 0..a.len() {
        match a[i] {
            b'a'..=b'z' => balance += 1,
            b'0'..=b'9' => balance -= 1,
            _ => panic!("Unknown character"),
        }
    }
    balance == 0
}
#[test]
fn test() {
    let tests = &[
        ("aaa1a1a1a1aaaa", 8),
        ("", 0),
        ("a1", 2),
        ("a1aaa", 2),
        ("1aaaa", 2),
        ("aaaaa1", 2),
        ("aaaa1a", 2),
    ];

    for &(test, size) in tests.iter() {
        let test = test.as_bytes();
        let is = letters_numbers_longest_subarray(test);
        assert!(is_balanced(is) && is.len() == size);
    }
}
