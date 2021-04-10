// 1.3 URLify

fn urlify(string: &mut [u8], true_length: usize) {
    // Expects the string to have space for the conversion.

    // First, count the number of spaces.

    let mut spaces_count = 0;

    for &i in &string[..true_length] {
        spaces_count += (i == b' ') as usize;
    }
    // Now, in the reverse direction, move each character to its position.

    let mut current_index = true_length - 1;

    loop {
        if string[current_index] != b' ' {
            string[current_index + spaces_count * 2] = string[current_index];
        } else {
            string[current_index + spaces_count * 2] = b'0';
            string[current_index + spaces_count * 2 - 1] = b'2';
            string[current_index + spaces_count * 2 - 2] = b'%';
            spaces_count -= 1;
        }
        if current_index == 0 {
            break;
        }
        current_index -= 1;
    }
}

#[test]
fn test() {
    for case in &[
        ("hello world  ", 11, "hello%20world"),
        ("a b c d      ", 7, "a%20b%20c%20d"),
    ] {
        let mut char_vec: Vec<u8> = case.0.bytes().collect();
        urlify(char_vec.as_mut_slice(), case.1);
        use std::str;
        assert!(str::from_utf8(char_vec.as_slice()).unwrap() == case.2);
    }
    println!("Ex 1.3 ok!");
}
