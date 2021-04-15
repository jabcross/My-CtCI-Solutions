// 17.12 BiNode

// As doubly-linked lists are a nightmare in Rust, I often implement them with
// shared owned storage in a Vec<Node>, and use `usize` as pointers.

struct Node {
    val: i32,
    node1: Option<usize>,
    node2: Option<usize>,
}

trait Tree {
    fn instance(&self, storage: &mut Vec<Node>) -> usize;
}

impl Tree for i32 {
    fn instance(&self, storage: &mut Vec<Node>) -> usize {
        let index = storage.len();
        storage.push(Node {
            val: *self,
            node1: None,
            node2: None,
        });
        index
    }
}

impl<L, R> Tree for (i32, L, R)
where
    L: Tree,
    R: Tree,
{
    fn instance(&self, storage: &mut Vec<Node>) -> usize {
        let index = storage.len();
        storage.push(Node {
            val: self.0,
            node1: None,
            node2: None,
        });
        let l_index = self.1.instance(storage);
        let r_index = self.2.instance(storage);
        storage[index].node1 = Some(l_index);
        storage[index].node2 = Some(r_index);
        index
    }
}

struct LLIterator {
    storage: Vec<Node>,
    current: Option<usize>,
}

impl Iterator for LLIterator {
    type Item = i32;
    fn next(&mut self) -> Option<Self::Item> {
        match self.current {
            None => None,
            Some(index) => {
                let rv = &self.storage[index];
                self.current = rv.node2;
                Some(rv.val)
            }
        }
    }
}

fn bin_tree_to_linked_list<T: Tree>(tree: T) -> LLIterator {
    let mut storage = Vec::new();
    let root = tree.instance(&mut storage);

    fn is_leaf(node: &Node) -> bool {
        node.node1.is_none() && node.node2.is_none()
    }

    // Transforms branch into linked list
    // Takes node's index in storage container
    // Returns indices of first and last node
    fn recurse(root: usize, storage: &mut Vec<Node>) -> (usize, usize) {
        let l = match storage[root].node1 {
            None => (root, root),
            Some(node1) => {
                if is_leaf(&storage[node1]) {
                    (node1, node1)
                } else {
                    recurse(node1, storage)
                }
            }
        };

        let r = match storage[root].node2 {
            None => (root, root),
            Some(node2) => {
                if is_leaf(&storage[node2]) {
                    (node2, node2)
                } else {
                    recurse(node2, storage)
                }
            }
        };

        if l.1 != root {
            storage[l.1 as usize].node2 = Some(root);
            storage[root as usize].node1 = Some(l.1);
        }
        if r.0 != root {
            storage[r.0 as usize].node1 = Some(root);
            storage[root as usize].node2 = Some(r.0);
        }
        (l.0, r.1)
    }

    let x = recurse(root, &mut storage);

    LLIterator {
        storage,
        current: Some(x.0),
    }
}

#[test]
fn test() {
    /*        4
     *       ↙ ↘
     *      2   6      =>   1⇋2⇋3⇋4⇋5⇋6⇋7
     *     ↙↓   ↓↘
     *    1 3   5 7
     *
     */
    assert!(
        bin_tree_to_linked_list((4, (2, 1, 3), (6, 5, 7))).collect::<Vec<_>>()
            == [1, 2, 3, 4, 5, 6, 7]
    )
}
