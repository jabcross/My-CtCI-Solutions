// 1.1 Is Uniqu

fn is_unique(string: &String)->bool {
    // Expects ascii characters. O(n) time, O(1) extra space
    
    // This solution keeps a table that keeps track of the number of times
    // a character has been seen. If it finds a character that has been seen
    // before, it returns false.

    let mut bitset: [u8; 256] = [0; 256];
    for character in string.bytes(){
        let index: usize = character as usize;
        if bitset[index] == 0 {
            bitset[index] = 1;
        }
        else {
            return false;
        }
    }
    return true;
}

fn is_unique_no_extra_space(string: &String)->bool {
    // Expects ascii characters. O(n^2), 0 extra space

    // For each character, scan the string until here to check for duplicates.

    for index in 1..string.len() {
        let slice = &string.as_bytes()[0..index-1];
        if slice.contains(&string.as_bytes()[index]){
            return false;
        }
    }
    return true;
}

pub fn test() {
    for f in &[is_unique, is_unique_no_extra_space] {
        assert!(f(&String::from("abcd")) == true);
        assert!(f(&String::from("")) == true);
        assert!(f(&String::from("a")) == true);
        assert!(f(&String::from("abba")) == false);
    }
    println!("Ex 1.1 ok!");
}