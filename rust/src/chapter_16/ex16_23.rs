// 16.23 Rand7 to Rand5

// Simply return the input if it's less than 5, and generate a new number
// otherwise. The expected number of iterations is about 1.8, which makes this
// algorithm ammortized 0(1).

// This expects that the original generator is truly random.

use rand::random;

fn rand7() -> usize {
    random::<usize>() % 7
}

fn rand7_to_rand5(r7: usize)->usize {
    assert!(r7 < 7);
    if r7 < 5 {
        r7
    }
    else {
        rand7_to_rand5(rand7())
    }
}

pub fn test(){
    let mut histogram = [0; 5];
    let sample_size : i32 = 100_000;
    for _ in 0..sample_size {
        let r7 = rand7();
        histogram[rand7_to_rand5(r7)] += 1;
    }
    assert!(histogram.iter().all(|x| {
        let expected = sample_size / 5;
        (expected - x).abs() < expected / 50 // 2% error
    }));

    println!("Ex 16.22 ok!");
}