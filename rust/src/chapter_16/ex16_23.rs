// 16.23 Rand7 from Rand5

// Compute rand25 from two rand5 calls.
// The highest power of 7 that fits is 21, so if the value is less than that
// you can evenly distribute values of mod 7.
// If the value is higher, try again.

// The expected number of recursions is
//
// 1 * 21/25 + 2 * 4/25 * 21/25 + 3 * (4/25)^2 * 21/25 + ... =
// = sum n=0->inf (n+1) (4/25)^n (21/25)
// = 25/21 ~ 1.1904762
//
// so, the complexity is ammortized O(1).

use std::usize;

use rand::random;

fn rand5() -> usize {
    random::<usize>() % 5
}

fn rand7(num_calls: usize) -> (usize, usize) {
    // 5 is less than 7, make a rand25 by adding another digit base 5

    let r25 = rand5() * 5 + rand5();

    if r25 < 21 {
        // from 0 to 20, there are 21 = 7 * 3 numbers. Return x / 3
        (r25 / 3, num_calls)
    } else {
        // Otherwise, try again
        rand7(num_calls + 1)
    }
}

pub fn test() {
    let mut histogram: [f64; 7] = [0.0; 7];
    let sample_size: usize = 100_000;
    let mut max_calls = 0;
    let mut total_calls = 0;
    for _ in 0..sample_size {
        let (result, calls) = rand7(1);
        histogram[result] += 1.0;
        max_calls = max_calls.max(calls);
        total_calls += calls;
    }
    let error = histogram
        .iter()
        .map(|x| {
            let expected = sample_size as f64 / 7.0;
            format!(
                "{:.2}%",
                (expected - x).abs() as f64 / expected as f64 * 100.0
            )
        })
        .collect::<Vec<_>>();

    println!(
        "Ex 16.23 deviation: {:?}, max_recursions: {}, average_recursions: {}",
        error,
        max_calls,
        total_calls as f64 / sample_size as f64
    );
}
