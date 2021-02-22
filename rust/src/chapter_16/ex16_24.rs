// 16.24 Pairs with Sum

// Depends on the constraints. A O(n) time and memory solution is
// to build a hash set with all values, and then look for the complement of each
// element. The hash can be stored for successive searches.

// On the worst case, there will be O(n^2) different sums. If there is enough memory, the results could be precomputed into a hash map of vectors. Not doing this here, though.

use std::collections::{HashMap, HashSet};

// returns unique pairs of indices (a,b), where a < b and vec[a] + vec[b] = sum
fn find_pairs_with_sum(vec: &[i32], sum: i32) -> HashSet<(usize, usize)> {
    let mut rv = HashSet::new();
    let mut hash: HashMap<i32, Vec<usize>> = HashMap::new();

    for (i, &j) in vec.iter().enumerate() {
        hash.entry(j).or_default().push(i);
    }

    for (&a, indices_a) in hash.iter() {
        let b = sum - a;
        if a == b {
            // add all equal pairs
            for i in 0..indices_a.len() {
                for j in i + 1..indices_a.len() {
                    rv.insert((indices_a[i], indices_a[j]));
                }
            }
        } else if a < b {
            if let Some(indices_b) = hash.get(&b) {
                for &i in indices_a {
                    for &j in indices_b {
                        rv.insert((i, j));
                    }
                }
            }
        }
    }
    rv
}

// just so I can sort a vector inline

trait Apply<U> {
    fn apply<F>(self, transform: F) -> U
    where
        Self: Sized,
        F: Fn(Self) -> U;
}

impl<T, U> Apply<U> for T
where
    T: Sized,
{
    fn apply<F>(self, transform: F) -> U
    where
        Self: Sized,
        F: Fn(T) -> U,
    {
        transform(self)
    }
}

pub fn test() {
    assert!({
        find_pairs_with_sum(&[1, 2, 3, 4, 5, 5, 6, 7, 8, 9], 10)
            .iter()
            .cloned()
            .collect::<Vec<(usize, usize)>>()
            .apply(|mut x| {
                x.sort();
                x
            })
            .iter()
            .zip(&[(0, 9), (1, 8), (2, 7), (3, 6), (4, 5)])
            .filter(|(a, b)| a != b)
            .count()
            == 0
    });
    println!("Ex 16.24 ok!");
}
