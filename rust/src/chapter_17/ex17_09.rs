// 17.9 Kth Multiple

// Set + heap, add 3x, 5x, 7x every iteration. O(nlogn) time, O(n) extra space.

use std::collections::HashSet;

use std::collections::BinaryHeap;

fn kth_multiple(index: usize) -> usize {
    if index == 0 {
        return 1;
    }

    let mut ordered = vec![];
    let mut heap = BinaryHeap::new();
    heap.push(-1);
    let mut seen = HashSet::new();

    while ordered.len() <= index {
        let x = -heap.pop().unwrap();
        for &i in &[x * 3, x * 5, x * 7] {
            if !seen.contains(&i) {
                heap.push(-i);
                seen.insert(i);
            }
        }
        ordered.push(x as usize);
    }

    ordered[index]
}

#[test]
fn test() {
    const TESTS: &[usize] = &[1, 3, 5, 7, 9, 15, 21, 25, 27];
    kth_multiple(6);
    for i in 0..TESTS.len() {
        let rv = kth_multiple(i);
        let test = TESTS[i];
        assert!(rv == test);
    }
}
