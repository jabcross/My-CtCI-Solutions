// 16.16 Sub Sort

fn sub_sort(array: &[i32]) -> (usize, usize) {

    // Returns inclusive bounds of minimal subarray that, if sorted,
    // makes so that the whole array is sorted.
    // Returns (0,0) if already sorted.
    
    // O(n) time, O(3n) space. I suspect it could be improved to O(n) time,
    // O(1) space.

    if array.len() == 0 {
        return (0,0);
    }
    if array.len() == 1 {
        return (0,0);
    }

    // Get tables with partial maxs and mins

    let mut min_from_right = vec![0; array.len()];
    let mut max_from_left = vec![0; array.len()];

    max_from_left[0] = array[0];


    for index in 1..array.len() {
        if array[index] > max_from_left[index - 1] {
            max_from_left[index] = array[index];
        }
        else {
            max_from_left[index] = max_from_left[index - 1];
        }
    }

    *min_from_right.last_mut().unwrap() = *array.last().unwrap();

    for index in (0..array.len()-1).rev() {
        if array[index] < min_from_right[index + 1] {
            min_from_right[index] = array[index];
        }
        else {
            min_from_right[index] = min_from_right[index + 1];
        }
    }

    // The range that needs to be sorted is from the first to the last place
    // where the partial min and max differ.

    let mut found_left = false;
    let mut left = 0;
    let mut right = 0;

    for index in 0..array.len() {
        if min_from_right[index] != max_from_left[index]{
            if !found_left {
                found_left = true;
                left = index;
            }
            right = index;
        }
    }

    return (left, right);

}

pub fn test() {
    assert!(sub_sort(&[1,2,4,7,10,11,7,12,6,7,16,18,19])==(3,9));
    assert!(sub_sort(&[1,2,3])==(0,0));
    assert!(sub_sort(&[3,2,1])==(0,2));
    assert!(sub_sort(&[])==(0,0));
    println!("Ex 16.16 ok!");
}