// 16.25 LRU Cache

// There are a couple of ways of doing this.

// A hash map with a doubly linked list is usually good, O(1) on access and O(n) in memory,
// but kinda tricky in Rust.
// I'm using a node pool instead of messing with references, here.

use std::{collections::HashMap, usize};

use i32 as Key;
use i32 as Value;

#[derive(Clone)]
struct LLNode {
    next: Option<usize>,
    prev: Option<usize>,
    key: Key,
    value: Value,
}
struct LRUCache {
    first: Option<usize>,
    last: Option<usize>,
    free_nodes: Vec<usize>,
    nodes: Vec<LLNode>,
    capacity: usize,
    hash: HashMap<Key, usize>,
}

impl LRUCache {
    fn get_idx(&mut self, index: usize) -> &mut LLNode {
        self.nodes.get_mut(index).unwrap()
    }

    fn new(capacity: usize) -> Self {
        LRUCache {
            first: None,
            last: None,
            free_nodes: Vec::new(),
            nodes: Vec::with_capacity(capacity),
            capacity,
            hash: HashMap::new(),
        }
    }

    fn get_free_node(&mut self) -> usize {
        self.free_nodes.pop().unwrap_or({
            if self.nodes.len() < self.capacity {
                self.nodes.push(LLNode {
                    next: None,
                    prev: None,
                    key: 0,
                    value: 0,
                });
                self.nodes.len() - 1
            } else {
                // drop first value

                let ret = self.first.unwrap();

                let next = self.get_idx(ret).next.unwrap();

                self.first = Some(next);
                self.get_idx(next).prev = None;

                let key = self.get_idx(ret).key;
                self.hash.remove(&key);

                ret
            }
        })
    }

    fn get(&self, key: Key) -> Option<Value> {
        self.hash.get(&key).map(|&x| self.nodes[x].value)
    }

    fn set(&mut self, key: Key, value: Value) {
        // see if node is already used
        let node = if let Some(v) = self.hash.remove(&key) {
            // is used. remove it from linked list

            let prev = self.get_idx(v).prev;
            let next = self.get_idx(v).next;

            if let Some(prev) = prev {
                self.get_idx(prev).next = next;
            }

            if let Some(next) = next {
                self.get_idx(next).prev = prev;
            }

            v
        } else {
            self.get_free_node()
        };

        self.first.get_or_insert(node);

        let last = self.last;
        self.get_idx(node).prev = last;
        if let Some(last) = last {
            self.get_idx(last).next = Some(node);
        }
        self.last = Some(node);
        self.get_idx(node).value = value;
        self.get_idx(node).key = key;
        self.get_idx(node).next = None;
        self.hash.insert(key, node);
    }
}

#[test]
fn test() {
    let mut cache = LRUCache::new(3);
    cache.set(1, 1);
    cache.set(2, 2);
    cache.set(3, 3);
    cache.set(4, 4);
    assert!(cache.get(1) == None);
    println!("Ex 16.25 ok!");
}
