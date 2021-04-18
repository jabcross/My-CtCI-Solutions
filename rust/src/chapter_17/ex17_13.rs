// 17.13 Re-Space

// Stores dictionary into trie.

// Complexity:
// n = size of text
// d = sum of lenghts of words in dictionary
// k = size of longest word
// Assuming words that share a prefix are not very common
//   (at most a constant number of overlaps per word. No cases like
//    "a", "aa", "aaa", ... )

// worst-case time: O(kn), space: (O(n))
// If n >>> k, k ~ constant, so time: O(n) and extra space: O(n)

// One memory optimization is to discard values that are more than k
// indices to the right of `start`. Then, we can have O(k) extra space.
// This only works if we're okay with streaming out the locations of the
// spaces in reverse order.

use std::collections::BTreeMap;
struct Trie {
    terminating: bool,
    next: BTreeMap<u8, Trie>,
}

impl Trie {
    fn new() -> Self {
        Trie {
            terminating: false,
            next: BTreeMap::new(),
        }
    }
    fn from(words: &[&[u8]]) -> Self {
        let mut rv = Self::new();
        for &word in words {
            rv.insert(word)
        }
        rv
    }
    fn insert(&mut self, word: &[u8]) {
        if word.is_empty() {
            return;
        }
        let mut next = self.next.entry(word[0]).or_insert_with(Trie::new);
        if word.len() == 1 {
            next.terminating = true;
        }
        next.insert(&word[1..]);
    }
    fn get_matches<'a>(&self, slice: &'a [u8]) -> Vec<(usize, usize)> {
        let mut trie = self;
        let mut rv = Vec::new();
        for i in 0..slice.len() {
            match trie.next.get(&slice[i]) {
                Some(x) => {
                    trie = x;
                    if trie.terminating {
                        rv.push((0, i + 1))
                    }
                }
                None => break,
            }
        }
        rv
    }
    fn contains(&self, slice: &[u8]) -> bool {
        if slice.is_empty() {
            return true;
        }
        match self.next.get(&slice[0]) {
            Some(trie) => trie.contains(&slice[1..]),
            None => false,
        }
    }
}

fn respace(dict: Trie, test: &[u8]) -> (Vec<&[u8]>, Vec<&[u8]>) {
    #[derive(PartialEq, Eq, PartialOrd, Ord, Clone, Copy)]
    struct Invariant {
        unrec: usize,
        l: usize,
        r: usize,
    }

    // (# unrecognized characters, slice of next recognized word)
    let mut dp: Vec<Invariant> = vec![
        Invariant {
            unrec: 0,
            l: 0,
            r: 0
        };
        test.len()
    ];
    dp[test.len() - 1] = if dict.contains(&test[(test.len() - 1)..]) {
        Invariant {
            unrec: 0,
            l: test.len() - 1,
            r: test.len(),
        }
    } else {
        Invariant {
            unrec: 1,
            l: test.len(),
            r: test.len(),
        }
    };

    for start in (0..test.len() - 1).rev() {
        // If no word starts here, copy next and add unrec char
        let mut best = dp[start + 1];
        best.unrec += 1;

        // For each possible word starting here (O(n))
        for (l, r) in dict.get_matches(&test[start..]).into_iter().rev() {
            let (l, r) = (l + start, r + start);

            if r == test.len() {
                // The whole slice is a word
                //
                //           /--match--\
                // .....................
                //           ^         ^
                //           l         r

                best = best.min(Invariant { unrec: 0, l, r });
            } else {
                // Only part of the string is a match
                //
                //           /--match--\/--tail--\
                // ...............................
                //           ^         ^
                //           l         r

                best = best.min(Invariant {
                    unrec: dp[r].unrec,
                    l,
                    r,
                });
            }
        }
        dp[start] = best;
    }

    let mut index = 0;
    let mut unrec_words = vec![];
    let mut words = vec![];

    while index < test.len() {
        let inv = dp[index];
        if index != inv.l {
            // This is a unrec word
            unrec_words.push(&test[index..inv.l]);
            words.push(&test[index..inv.l]);
        }
        words.push(&test[inv.l..inv.r]);
        index = inv.r;
    }
    (unrec_words, words)
}

#[test]
fn test() {
    // let mut trie = Trie::from(&[b"abra", b"abracadabra"]);

    // for i in trie.get_matches(b"abracadabra") {
    //     println!("{:?}", std::str::from_utf8(i).unwrap());
    // }

    let dict: &[&[u8]] = &[b"looked", b"just", b"like", b"her", b"brother"];

    let dict = Trie::from(dict);

    let test = b"jesslookedjustliketimherbrother";
    let (unrec, words) = respace(dict, test);
    let expected_unrec: &[&[u8]] = &[b"jess", b"tim"];
    let expected_words: &[&[u8]] = &[
        b"jess", b"looked", b"just", b"like", b"tim", b"her", b"brother",
    ];
    for i in &words {
        println!("{:?}", std::str::from_utf8(i).unwrap());
    }
    assert!(unrec == expected_unrec);
    assert!(words == expected_words);
}
