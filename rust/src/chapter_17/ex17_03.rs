use rand::Rng;

// 17.3 Random set

pub fn random_set(vector: &[i32], size: usize) -> Vec<i32> {
    assert!(size <= vector.len());
    let mut placeholder_vec: Vec<_> = vector.to_vec();
    for i in 0..size {
        placeholder_vec.swap(i, rand::thread_rng().gen_range(i, vector.len() - 1));
    }
    placeholder_vec.truncate(size);
    placeholder_vec
}

#[test]
fn test() {
    let x = random_set(&rand::random::<[i32; 10]>(), 5);
    assert!(x.len() == 5);
    println!("Ex 17.3 assumed ok");
}
