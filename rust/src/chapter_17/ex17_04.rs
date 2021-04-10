// 17.4 Missing Number

// Considering the size of the integer is constant (32 bits, in this case),
// the algorithm runs in O(N) with O(1) extra space.
// Could also be done by adding and subtracting, but then we'd have to worry
// about overflow issues.

fn fetch_jth_bit_of_a_i(a: &[u32], i: usize, j: usize) -> u32 {
    (a[i] >> j) & 1
}

// Finds single missing number in array from 0 to A.len()
fn find_missing_number(a: &[u32]) -> u32 {
    let mut total_xor: u32 = 0;
    let mut array_xor: u32 = 0;
    for i in 0..a.len() {
        total_xor ^= i as u32;
        for j in 0..32 {
            array_xor ^= fetch_jth_bit_of_a_i(a, i, j) << j;
        }
    }
    total_xor ^= a.len() as u32;
    total_xor ^ array_xor
}

#[test]
fn test() {
    let test1 = [0, 1, 2, 3, 4, /*5,*/ 6, 7, 8, 9, 10];
    let x = find_missing_number(&test1);
    assert!(x == 5);
}
