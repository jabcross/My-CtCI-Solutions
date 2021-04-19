// 17.15 Longest Word

// Complexity: O(n*k^2) where n is the number of words and k is the
// length of longest word. Size: O(n*k)

struct Trie {
    terminating: bool,
    next: std::collections::BTreeMap<u8, Trie>,
}

impl Trie {
    fn new() -> Self {
        Trie {
            terminating: false,
            next: std::collections::BTreeMap::new(),
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

// returns 0 if string is not in dictionary,
//         1 if string is not made of other words,
//         x > 1 if string is made of other words.

fn count_words<'a>(
    trie: &Trie,
    word: &'a [u8],
    cache: &mut std::collections::HashMap<&'a [u8], usize>,
) -> usize {
    if let Some(x) = cache.get(word) {
        return *x;
    }
    let matches = trie.get_matches(word);
    let mut rv = 0;
    for _match in matches {
        if _match.1 < word.len() {
            let rec = count_words(trie, &word[.._match.1], cache);
            if rec > 0 {
                rv = 1 + rec;
                break;
            }
            continue;
        }
        if _match.1 == word.len() {
            rv = 1;
            break;
        }
    }
    cache.insert(word, rv);
    rv
}

fn longest_word<'a>(words: &[&'a [u8]]) -> Option<&'a [u8]> {
    let trie = Trie::from(words);

    let mut best: Option<(usize, &[u8])> = None;
    let mut cache = std::collections::HashMap::new();

    for &word in words {
        if count_words(&trie, word, &mut cache) <= 1 {
            continue;
        }
        best = best.max(Some((word.len(), word)));
    }
    best.map(|x| x.1)
}

#[test]
fn test() {
    let test: &[&[u8]] = &[
        b"cat",
        b"banana",
        b"dog",
        b"nana",
        b"walk",
        b"walker",
        b"dogwalker",
    ];
    let expected = b"dogwalker";
    assert_eq!(longest_word(test).unwrap(), expected);
}
