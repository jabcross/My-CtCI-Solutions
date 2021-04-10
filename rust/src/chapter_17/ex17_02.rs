// 17.2 Shuffle

// Does 51 swaps, similar to quicksort

fn shuffle(generator: &dyn Fn() -> usize) -> Vec<usize> {
    let mut numbers = (0..52).collect::<Vec<_>>();
    for i in (1..52).rev() {
        let chosen_index = generator() % (i + 1);
        numbers.swap(chosen_index, i);
    }
    numbers
}

#[test]
fn test() {
    use rand::random;

    println!("Ex 17.2: Generated: {:?}", shuffle(&random::<usize>));
}
