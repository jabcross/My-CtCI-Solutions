// 17.8 Circus Tower

// Computes DAG, finds longest path. O(n^2) time and space.

use std::collections::HashMap;
type Person = usize;
struct Graph {
    can_go_higher: HashMap<Person, Vec<Person>>,
}

impl Graph {
    fn add_edge(&mut self, small: Person, big: Person) {
        self.can_go_higher
            .entry(big)
            .or_insert_with(Vec::new)
            .push(small);
        // self.can_go_lower.entry(small).or_insert(vec![]).push(big);
    }
    fn find_farthest(
        &self,
        farthest_cache: &mut HashMap<Person, (usize, Person, Person)>,
        person: Person,
    ) -> (usize, Person, Person) {
        if let Some(x) = farthest_cache.get(&person) {
            return *x;
        }
        let mut furthest = (0, person, person);
        if let Some(nexts) = self.can_go_higher.get(&person) {
            for next in nexts {
                let (dist, _nextnext, furthest_from_next) =
                    self.find_farthest(farthest_cache, *next);
                furthest = furthest.max((dist + 1, *next, furthest_from_next));
            }
        }
        farthest_cache.insert(person, furthest);
        furthest
    }
}

fn circus_tower(people: &[(usize, usize)]) -> Vec<(usize, usize)> {
    let mut graph = Graph {
        can_go_higher: HashMap::new(),
    };

    for i in 0..people.len() {
        for j in 0..i {
            if people[i].0 > people[j].0 && people[i].1 > people[j].1 {
                graph.add_edge(i, j);
            } else if people[i].0 < people[j].0 && people[i].1 < people[j].1 {
                graph.add_edge(j, i);
            }
        }
    }
    let mut largest_path = (0usize, 0usize, 0usize);
    let mut cache = HashMap::new();
    for a in 0..people.len() {
        let (dist, _next, b) = graph.find_farthest(&mut cache, a);
        largest_path = largest_path.max((dist, a, b));
    }
    let mut rv = Vec::new();
    let mut a = largest_path.1;
    loop {
        rv.push(people[a]);
        let &(dist, next, end) = cache.get(&a).unwrap();
        if a == end {
            break;
        }
        a = next;
    }
    rv
}

#[test]
fn test() {
    const TESTS: (&[(usize, usize)], &[(usize, usize)]) = (
        &[
            (65, 100),
            (70, 150),
            (56, 90),
            (75, 190),
            (60, 95),
            (68, 110),
        ],
        &[
            (56, 90),
            (60, 95),
            (65, 100),
            (68, 110),
            (70, 150),
            (75, 190),
        ],
    );
    let result = circus_tower(TESTS.0);
    println!("{:?}", result);
    assert!(result == TESTS.1);
}
