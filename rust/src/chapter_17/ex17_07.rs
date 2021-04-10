// 17.7 Baby names

// Uses the UnionSet data structure, which has ammortized O(1)
// insertion and retrieval.

use std::collections::HashMap;

trait UnionSet<Id> {
    fn join(&mut self, a: Id, b: Id);
    fn get_union(&mut self, id: Id) -> Id;
}

impl UnionSet<usize> for HashMap<usize, usize> {
    fn join(&mut self, a: usize, b: usize) {
        let a_parent = *self.entry(a).or_insert(a);
        let b_parent = *self.entry(b).or_insert(a);
        self.insert(b_parent, a_parent);
    }
    fn get_union(&mut self, id: usize) -> usize {
        let mut id = id;
        loop {
            let parent = *self.get(&id).unwrap();
            if id == parent {
                break;
            }
            id = parent;
        }
        id
    }
}

struct BabyNames {
    name_ids: HashMap<&'static str, usize>,
    union_set: HashMap<usize, usize>,
    counts: HashMap<usize, usize>,
}

impl BabyNames {
    fn from(frequencies: &[(&str, usize)], equivalencies: &'static [(&str, &str)]) -> Self {
        let mut index = 0;
        let mut name_ids = HashMap::new();
        let mut counts = HashMap::new();
        let mut union_set = HashMap::new();

        let mut get_new_index = || {
            let x = index;
            index += 1;
            x
        };

        for &(a, b) in equivalencies.iter() {
            let a_index = *name_ids.entry(a).or_insert_with(&mut get_new_index);
            let b_index = *name_ids.entry(b).or_insert_with(&mut get_new_index);
            union_set.join(a_index, b_index);
        }
        for (name, count) in frequencies {
            let id = *name_ids.get(name).unwrap();
            let id = union_set.get_union(id);
            let val = counts.entry(id).or_insert(0usize);
            *val += *count;
        }
        BabyNames {
            name_ids,
            union_set,
            counts,
        }
    }

    fn get_count(&mut self, name: &str) -> usize {
        let id = self.name_ids.get(name).unwrap();
        let parent_id = self.union_set.get_union(*id);
        *self.counts.get(&parent_id).unwrap()
    }
}

#[test]
fn test() {
    const TESTS: &[(&[(&str, usize)], &[(&str, &str)], &[(&str, usize)])] = &[(
        &[
            ("John", 15),
            ("Jon", 12),
            ("Chris", 13),
            ("Kris", 4),
            ("Christopher", 19),
        ],
        &[
            ("Jon", "John"),
            ("John", "Johnny"),
            ("Chris", "Kris"),
            ("Chris", "Christopher"),
        ],
        &[("John", 27), ("Kris", 36)],
    )];

    for test in TESTS {
        let mut babynames = BabyNames::from(test.0, test.1);
        for (name, count) in test.2 {
            assert!(babynames.get_count(name) == *count);
        }
    }
}
