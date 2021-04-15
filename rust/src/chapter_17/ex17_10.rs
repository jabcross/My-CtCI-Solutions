// 17.10 Majority Element

// O(n) time, O(1) extra space

fn maj_element(items: &[usize]) -> i32 {
    if items.is_empty() {
        return -1;
    }
    let mut current = items[0];
    let mut count = 1;
    for &i in &items[1..] {
        if current == i {
            count += 1;
        } else {
            count -= 1;
        }
        if count == 0 {
            current = i;
            count = 1;
        }
    }
    let amount = items.iter().filter(|x| **x == current).count();
    if amount > items.len() / 2 {
        return current as i32;
    }
    -1
}

#[test]
fn test() {
    assert!(maj_element(&[1, 2, 5, 9, 5, 9, 5, 5, 5]) == 5);
    assert!(maj_element(&[1]) == 1);
    assert!(maj_element(&[]) == -1);
    assert!(maj_element(&[1, 1, 2]) == 1);
    assert!(maj_element(&[1, 2, 1]) == 1);
    assert!(maj_element(&[2, 1, 1]) == 1);
    assert!(maj_element(&[5, 5, 5, 1, 1]) == 5);
    assert!(maj_element(&[1, 2, 3, 4, 5]) == -1);
}
