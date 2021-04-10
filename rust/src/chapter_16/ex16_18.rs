// 16.18 Pattern Matching

use std::collections::HashMap;

fn match_pattern<'a>(
    string: &'a str,
    pattern: &'a str,
    pattern_attempts: &mut HashMap<&'a str, &'a str>,
) -> bool {
    // Returns true if the string can be subdivided in substrings that match
    // the pattern. This is a simple recursive implementation, which checks if
    // a pattern is already being considered by checking it against a hash map.
    // There are ways to optimize this, for instance by calculating the expected
    // size of the string when all symbols have a candidate.

    if pattern.len() == 0 {
        return string.len() == 0;
    }

    match pattern_attempts.get(&pattern[0..1]) {
        Some(slice) => {
            if string.starts_with(*slice) {
                match_pattern(&string[slice.len()..], &pattern[1..], pattern_attempts)
            } else {
                false
            }
        }
        None => {
            if (pattern.len() == 1) && (string.len() > 0) {
                return true;
            }
            for length in 1..string.len() + 1 {
                pattern_attempts.insert(&pattern[0..1], &string[0..length]);
                let result = match_pattern(&string[length..], &pattern[1..], pattern_attempts);
                pattern_attempts.remove(&pattern[0..1]);
                if result {
                    return true;
                }
            }
            false
        }
    }
}

#[test]
fn test() {
    assert!(match_pattern("catcatgocatgo", "aabab", &mut HashMap::new()));
    assert!(match_pattern("catcatgocatgo", "a", &mut HashMap::new()));
    assert!(match_pattern("catcatgocatgo", "ab", &mut HashMap::new()));
    assert!(match_pattern("catcatgocatgo", "b", &mut HashMap::new()));
    assert!(!match_pattern("dog", "aba", &mut HashMap::new()));
    println!("Ex 16.18 ok!");
}
