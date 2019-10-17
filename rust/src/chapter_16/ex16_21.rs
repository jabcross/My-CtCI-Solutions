// 16.21 Sum Swap

// This solution uses a hash map to register values of a vector that get
// accessed by the values in the other vector.

// First we scan both vectors to calculate their sum, and subtract them
// to get the difference d. We need to transfer half this difference from the
// vector with least sum to the other vector, and so we are looking for a 
// pair that is d / 2 apart. If this difference is odd, we
// can fail, since the value we must transfer is fractional.

// Knowing this value, for each value a of A, only one possible value must be in
// B for the swap to be correct: A - d/2.

// Takes O(len(a) + len(b)) time, O(len(b)) extra space. We can swap A and B
// after calculating the sums to take O(min(len(a),len(b))) instead.

fn sum(vector: &[i32])->i32{
    use std::ops::Add;
    vector.iter().fold(0, i32::add)
}

fn sum_swap(a: &[i32], b:&[i32]) -> Option<(i32, i32)> {
    let sum_a = sum(a);
    let sum_b = sum(b);
    let difference = sum_a - sum_b;

    if difference % 2 == 1 {
        return None;
    }

    let half_difference = difference / 2;

    use std::collections::HashSet;
    use std::iter::FromIterator;

    let set: HashSet<i32> = HashSet::from_iter(b.iter().cloned());

    for value_in_a in a {
        if set.contains(&(value_in_a - half_difference)) {
            return Some((*value_in_a, value_in_a - half_difference));
        }
    }

    None
}

fn test_instance(a: &[i32], b:&[i32])-> bool {
    if let Some((from_a, from_b)) = sum_swap(a,b){
        return sum(a) - from_a + from_b ==  sum(b) - from_b + from_a;
    }
    else {
        false
    }
}

pub fn test(){
    assert!(test_instance(&[4, 1, 2, 1, 1, 2], &[3, 6, 3, 3]));
    println!("Ex 16.21 ok!");
}