// 17.16 Masseusse

// Simple DP.
// bests_without[i] = best solution that excludes requests[i].
//                  = bests[i-1].
// bests[i] = best solution that may include requests[i]
//          = max ( bests_without[i-1] + requests[i] ,
//                  bests_without[i] )
//

// O(n) spacetime. Note that the solution in the book uses O(1) space,
// but it doesn't return a list of accepted requests.

fn masseuse(requests: &[usize]) -> Vec<usize> {
    // (total_value, used_this)
    let mut bests = vec![(30, true)]; // use first value
    let mut bests_without = vec![(0, false)]; // don't use first value

    for i in 1..requests.len() {
        let best_without = (bests[i - 1].0, false);
        let prev_b_w = bests_without[i - 1];
        let best = (prev_b_w.0 + requests[i], true).max(best_without);
        bests.push(best);
        bests_without.push(best_without);
    }
    let mut rv = vec![];
    let mut use_best = true;
    let mut index = requests.len() - 1;
    loop {
        let used_this = if use_best {
            bests[index].1
        } else {
            bests_without[index].1
        };

        if used_this {
            rv.push(requests[index]);
        }
        use_best = !used_this;

        if index == 0 {
            break;
        };
        index -= 1;
    }
    rv.reverse();
    rv
}

#[test]
fn test() {
    let test: &[usize] = &[30, 15, 60, 75, 45, 12, 12, 45];
    //                30   15   60   75   45   12   12   45
    // bests          30t  30f  90t 105t 135t 135f 147t 180t
    // bests_without   0f  30f  30f  90f 105f 135f 135f 147f

    let expected: &[usize] = &[30, 60, 45, 45];
    assert_eq!(masseuse(test), expected);
}
