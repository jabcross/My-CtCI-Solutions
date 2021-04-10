// 17.6 Count of 2s

// Return number of 2s in decimal representation of n

// O(log(n)) time and space. If k is the number of digits, at most 7k
// different calls will be made.

/*
Analysis:

    let x,y,z,...w the k digits of n,
    T(p) is the number of recursive calls made by f(p)
    x > 2
    1e(k+1) > n >= 1ek
    cost of a function call = 1
    for d ∈ (0,9), T(d) = 1
    2ek = 2 * 10 ^ k (scientific notation)

    T(xyz...w) = T(3ek - 1) + T(1ek - 1)  + T(xe(k-1)) + call
    xyz...w      2999...      0999...       yz...w

    T(3ek - 1) = T(2ek - 1) + T(1ek - 1) + call
    2999...      1999...      0999...

    T(2ek - 1) = T(1ek - 1) + T(1ek - 1) + call
    1999...      0999...       0999...

    T(1ek - 1) = T(3e(k-1) - 1) + T(1e(k-1) - 1) + call
    0999...      0299...          0099...  ^
                                           |
    T(3ek - 1) calls T(1ek-1), so it is cached

    therefore,

    T(1ek - 1) = T(3e(k-1) - 1) + 1(cached) + call
               = T(3e(k-1) - 1) + 2

T(3ek - 1) =
    T(2ek - 1)
        T(1ek - 1)
            T(3e(k-1) - 1)
            2
        T(1ek - 1) = 1 #cached
        call = 1
    T(1ek - 1) = 1 #cached
    call = 1

=>

T(3ek - 1) = T(3e(k-1) - 1) + 6

T(3k1 - 1) = T(29) = T(19) + T(9) + call = T(9) + T(9) + call + T(9) + call = 5

By induction, T(29) = 5, T(299) = 11, T(2999) = 17
            T(3ek - 1) = 6k - 1

T(xyz...w) = T(3ek - 1) + T(1ek - 1)  + T(yz...w) + call
        = 6k-1 + 1(cached) + T(yz...w)
        = 6k + T(yz...w)

For T(yzw), considering all calls of form T(99..), T(299..), T(199) are cached:

(1ek > yzw...> 1e(k-1))

T(yz..w) = 1 + 1 + T(z...w) + call = 3 + T(z...w)
T(w) = 1 -> T(..w) = 3w -> T(yz..w) = 3(k-2)+1 = 3k -5


So, T(xyz...w) = 6k + 3k - 5 = 9k - 5 = O(log(n)).

*/

use std::collections::HashMap;

fn count_2s(n: usize, cache: &mut HashMap<usize, usize>) -> usize {
    if n < 10 {
        return (n >= 2) as usize;
    }

    if let Some(x) = cache.get(&n) {
        return *x;
    }

    let mut _10_to_i = 1; // 1, 10, 100, 1000 etc
    let mut msd = n; // most significant digit
    while msd / 10 > 0 {
        _10_to_i *= 10;
        msd /= 10;
    }

    if msd == 1 {
        // example: 157
        let head = _10_to_i; // 100
        let tail = n - head; // 57

        // f(157) = f(99) + f(57)
        //          0..99 + 100..157
        return count_2s(head - 1, cache) + count_2s(tail, cache);
    }

    if msd == 2 {
        // example: 257
        let head = 2 * _10_to_i; // 200
        let tail = n - head; // 57

        // f(254) = f(199) + 1   + f(54)      + 54
        //                   _      __   __   _    _
        //          0..157   200   201..257   201..257

        return count_2s(head - 1, cache) + 1 + count_2s(tail, cache) + tail;
    }
    // example: 657
    let magnitude = _10_to_i; // 100
    let head = magnitude * msd; // 600
    let tail = n - head; // 57

    // f(657) = f(299) + (6-3) * f(99) + f(57)
    //          0..299   300..600        601..657

    count_2s(3 * magnitude - 1, cache)
        + (msd - 3) * count_2s(magnitude - 1, cache)
        + count_2s(tail, cache)
}

fn proof(n: usize) -> usize {
    let mut acc = 0;
    for i in 0..=n {
        let mut i_ = i;
        while i_ > 0 {
            acc += (i_ % 10 == 2) as usize;
            i_ /= 10;
        }
    }
    acc
}

#[test]
fn test() {
    let mut cache = HashMap::new();
    count_2s(20, &mut cache);
    let mut i = 1;
    for _ in 0..8 {
        let a = count_2s(i - 1, &mut cache);
        let b = proof(i - 1);
        assert!(a == b);
        i *= 10;
    }
}
