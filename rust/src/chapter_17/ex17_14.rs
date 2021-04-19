// 17.14 Smallest K

// Complexity: O(n) (expected)

use rand::{prelude::SliceRandom, random};
use std::{collections::BinaryHeap, ops::Shr};

// returns (low, eq, high) where
//   low = number of elements lower than pivot, and index of first pivot
//   eq = number of elements equal to pivot,
//   hight = number of elements higher than pivot.
fn partition<T: Eq + Ord + Copy>(array: &mut [T], pivot: T) -> (usize, usize, usize) {
    let mut low_index = 0;

    // Would have to be a vector if didn't have total equality
    let mut eq_count = 0;

    let mut high_index = array.len();

    let mut i = 0;

    while i < high_index {
        if array[i] < pivot {
            array.swap(i, low_index);
            low_index += 1;
            i += 1;
        } else if array[i] > pivot {
            high_index -= 1;
            array.swap(i, high_index);
        } else {
            // equals
            eq_count += 1;
            i += 1;
        }
    }

    for i in low_index..high_index {
        array[i] = pivot;
    }

    (low_index, eq_count, low_index + eq_count)
}

// Reorders the array so that the k smallest
// elements are in the k first positions (not
// necessarily ordered)
fn partition_smallest(list: &mut [usize], k: usize) {
    assert!(!list.is_empty());
    let pivot = *list.choose(&mut rand::thread_rng()).unwrap();
    let (low, _equal, high) = partition(list, pivot);
    if k < low {
        partition_smallest(&mut list[..low], k);
    } else if k > high {
        partition_smallest(&mut list[high..], k - high);
    }
}

#[test]
fn test() {
    let test: &mut [usize] = &mut [10, 1, 9, 2, 8, 3, 7, 4, 6, 5];
    let expected = [1, 2, 3];
    assert_eq!(
        {
            partition_smallest(test, 3);
            let x = &mut test[..3];
            x.sort_unstable();
            &test[..3]
        },
        expected
    );
}
