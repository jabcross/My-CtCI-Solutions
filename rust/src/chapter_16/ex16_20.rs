// 16.20 T9

// This solution uses a Trie.
// We build a trie with the dictionary, but with corresponding digits as keys
// instead of letters. Each terminating digit has a list of valid strings.
// This has setup time O(total_num_characters_in_dictionary) and query time 
// O(length_query). This is good for long words, because each keystroke has only
// O(num_current_valid_words) time.



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

    fn get(&self, numbers: &'a str) -> Option<&Vec<&'a str>> {
        if numbers.len() == 0 {
            return Some(&self.terminators);
        }
        else {
            match &self.next {
                None => None,
                Some(hashmap) => {
                    match hashmap.get(&numbers[0..1]) {
                        Some(node) => {
                            node.get(&numbers[1..])
                        },
                        None => None
                    }
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

fn t9<'a>(trie: &'a TrieNode, input: &'a str) -> Vec<&'a str> {
    // Returns possible words that this input could correspond to.

    // Uses a premade trie that maps the input to the possible words.
    let mut rv = Vec::new();

    if let Some(vector) = trie.get(input) {
        for word in vector {
            rv.push(*word);
        }
    }

    rv
}


// Hash Map implementation

// An alternative would be using a hash map to connect digit sequences to
// string lists. It takes slighly more space and has O(length_of_query) for each
// keystroke, but for small word sizes it should make little difference. It's
// also easier to implement.

struct HashT9 {
    hash_map: HashMap<String, Vec<&'static str>>
}

impl HashT9 {
    pub fn from_words(words: &[&'static str]) -> Self {
        let mut rv = HashT9 {
            hash_map: HashMap::new()
        };

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

        for &word in words {

            let mut digits = String::new();
            for character in word.chars() {

                let char_string = 
                    {
                        let mut x = String::new();
                        x.push(character);
                        x
                    };
                
                digits += letter_to_number.get(char_string.as_str()).unwrap();

            }

            let digits = digits;

            rv.hash_map.entry(digits).or_insert(Vec::new()).push(word);

        }

        rv
    }

    pub fn get(&self, string: &str) -> Vec<&'static str> {
        if let Some(vector) = self.hash_map.get(&String::from(string)){
            vector.clone()
        }
        else {
            Vec::new()
        }
    }
}


pub fn test(){
    let words : &[&'static str] = &[
        "used",
        "tree",
        "car",
        "road"
    ];

    let trie = build_trie(words);

    let hasht9 = HashT9::from_words(words);

    assert!(["tree", "used"].iter().all(|x| t9(&trie, "8733").contains(x)));
    assert!(["tree", "used"].iter().all(|x| hasht9.get("8733").contains(x)));
    println!("Ex 16.20 ok!");
}