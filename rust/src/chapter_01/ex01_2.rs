// 1.2 Check Permutation

fn check_permutation(string_a: &str, string_b: &str) -> bool {
    // Expects ascii characters. O(a + b) time, O(1) extra space

    // Similar to ex1.1's solution, we keep one character counter for each
    // string. In the end, we compare the counters; permutations should
    // generate the same counter array.

    if string_a.len() != string_b.len() {
        return false;
    }

    let mut char_counter_a: [u8; 256] = [0; 256];
    let mut char_counter_b: [u8; 256] = [0; 256];
    for character in string_a.bytes() {
        let index: usize = character as usize;
        char_counter_a[index] += 1;
    }
    for character in string_b.bytes() {
        let index: usize = character as usize;
        char_counter_b[index] += 1;
    }

    for index in 0..256 {
        if char_counter_a[index] != char_counter_b[index] {
            return false;
        }
    }
    true
}

#[test]
fn test() {
    assert!(check_permutation("", ""));
    assert!(check_permutation("a", "a"));
    assert!(check_permutation("ab", "ba"));
    assert!(!check_permutation("aa", "ab"));
    assert!(!check_permutation("aa", "a"));
    println!("Ex 1.2 ok!");
}
