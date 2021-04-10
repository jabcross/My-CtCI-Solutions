// 16.16 Contiguous Sequence

fn contiguous_sequence(array: &[i32]) -> (usize, usize) {
    // Returns inclusive bounds of subarray with maximal sum.

    // O(n) time, O(1) space.

    // We iterate through the array, keeping the maximal subarray and
    // maximal suffix as invariants. When a new element is better than
    // the whole suffix, the old suffix is abandoned. As every subarray
    // was a suffix at some point, we just keep the maximal encountered
    // suffix.

    if array.is_empty() {
        return (0, 0);
    }

    if array.len() == 1 {
        return (0, 0);
    }

    let mut left = 0;
    let mut right = 0;
    let mut subarray_sum = array[0];

    let mut left_suffix = 0;
    let mut suffix_sum = array[0];

    for index in 1..array.len() {
        if array[index] > array[index] + suffix_sum {
            left_suffix = index;
            suffix_sum = array[index];
        } else {
            suffix_sum += array[index];
        }

        if suffix_sum > subarray_sum {
            left = left_suffix;
            right = index;
            subarray_sum = suffix_sum;
        }
    }

    (left, right)
}

#[test]
fn test() {
    assert!(contiguous_sequence(&[2, -8, 3, -2, 4, -10]) == (2, 4));
    println!("Ex 16.17 ok!");
}
