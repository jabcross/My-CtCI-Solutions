// 16.20 T9

use std::collections::HashSet;
use std::collections::HashMap;

#[derive(Debug)]
struct TrieNode<'a> {
    terminators: Vec<&'a str>,
    next: Option<HashMap<&'a str, TrieNode<'a>>>
}

impl <'a> TrieNode <'a> {
    fn new()->Self {
        return TrieNode {
            terminators: vec![],
            next: None
        }
    }

    fn insert (&mut self, word: &'a str, slice: &'a str, letter_to_number: &HashMap<&'a str, &'a str>){
        if slice.len() == 0 {
            self.terminators.push(word);
        }
        else {
            if let None = self.next {
                self.next = Some(HashMap::new());
            }
            let key = letter_to_number[&slice[0..1]];
            if let Some(hashmap) = &mut self.next {
                if let None = hashmap.get_mut(key) {
                    hashmap.insert(key, Self::new());
                }
                if let Some(node) = hashmap.get_mut(key) {
                    node.insert(word, &slice[1..], letter_to_number);
                }
            }
        }
    }
}

fn build_trie<'a> (words: &[&'a str]) -> TrieNode<'a> {
    let number_to_letter :HashMap<&str, Vec<&str>> = [
        ("2",vec!["a","b","c"]),
        ("3",vec!["d","e","f"]),
        ("4",vec!["g","h","i"]),
        ("5",vec!["j","k","l"]),
        ("6",vec!["m","n","o"]),
        ("7",vec!["p","q","r","s"]),
        ("8",vec!["t","u","v"]),
        ("9",vec!["w","x","y","z"])
    ].iter().cloned().collect();

    let mut letter_to_number: HashMap<&str, &str> = HashMap::new();

    for (key, value) in &number_to_letter {
        for letter in value {
            letter_to_number.insert(*letter, *key);
        }
    }


    let mut rv = TrieNode{
        terminators: vec![],
        next: None
    };

    for word in words {
        rv.insert(word, word, &letter_to_number);
    }

    rv
}

fn t9<'a>(trie: &'a TrieNode, input: &'a str) -> HashSet<&'a str> {
    // Returns possible words that this input could correspond to.

    // Uses a premade trie that maps the input to the possible words.
    let mut rv = HashSet::new();

    let mut slice = input;
    let mut node = trie;

    loop {
        if slice.len() == 0 {

            for item in &node.terminators {
                rv.insert(*item);
            }
            break();
        }
        else {
            match &node.next {
                Some(map) => {
                    match map.get(&slice[0..1]) {
                        Some(_node) => {
                            slice = &slice[1..];
                            node = _node;
                            continue;
                        }
                        _=>{break;}
                    }
                },
                _=> {break;}
            }
        }
    }


    rv
}

pub fn test(){
    let words : &[&'static str] = &[
        "used",
        "tree",
        "car",
        "road"
    ];

    let trie = build_trie(words);

    assert!(["tree", "used"].iter().all(|x| t9(&trie, "8733").contains(x)));
    println!("ex 16.20 ok!");
}