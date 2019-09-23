// 1.3 URLify

fn urlify(string: &mut [u8], true_length: usize){
    // Expects the string to have space for the conversion.

    // First, count the number of spaces.

    let mut spaces_count = 0;
    for index in 0..true_length {
        if string[index] == ' ' as u8 {
            spaces_count += 1;
        }
    }

    // Now, in the reverse direction, move each character to its position.

    let mut current_index = true_length - 1;

    loop {
        if string[current_index] != ' ' as u8 {
            string[current_index + spaces_count * 2] = string[current_index];
        }
        else {
            string[current_index + spaces_count * 2] = '0' as u8;
            string[current_index + spaces_count * 2 - 1] = '2' as u8;
            string[current_index + spaces_count * 2 - 2] = '%' as u8;
            spaces_count -= 1;
        }
        if current_index == 0 {
            break;
        }
        current_index -= 1;
    }

}

pub fn test() {
    for case in &[
            ("hello world  ", 11, "hello%20world"),
            ("a b c d      ", 7, "a%20b%20c%20d")] {
        let mut char_vec : Vec<u8> = case.0.bytes().collect();
        urlify(char_vec.as_mut_slice() , case.1);
        use std::str;
        assert!(str::from_utf8(char_vec.as_slice()).unwrap() == case.2);
    }
    println!("Ex 1.3 ok!");
}