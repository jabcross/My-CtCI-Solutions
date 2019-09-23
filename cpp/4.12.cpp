#include <bits/stdc++.h>

using namespace std;

struct BT_Node {
    int      value = 0;
    BT_Node *left = NULL, *right = NULL;
};

int recurse(BT_Node* root, unordered_map<int, int >& table, int sum, int running) {
    if (!root) return 0;
    int rv = 0;
    running += root->value;

    if (table.find(running) == table.end()){
        table[running] = 0;
    }

    if (table.find(running - sum) == table.end()){
        table[running - sum] = 0;
    }
    rv = table[running - sum];

    if (running == sum){
        rv ++;
    }

    table[running] ++;
    rv += recurse(root->left, table, sum, running);
    rv += recurse(root->right, table, sum, running);
    table[running] --;


    return rv;
}

int count_paths_with_sum(BT_Node* root, int sum) {
    if (!root) return 0;
    unordered_map<int, int > table;
    int rv = recurse(root, table, sum, 0);
    return rv;
}

int main() {
    auto root = new BT_Node;
    root->value = 10;
    root->left = new BT_Node;
    root->left->value = 5;
    root->right = new BT_Node;
    root->right->value = 3;
    root->right->left = new BT_Node;
    root->right->left->value = 2;
    assert (count_paths_with_sum(root, 15) == 2);
    assert (count_paths_with_sum(root, 5) == 2);
    assert (count_paths_with_sum(root, 2) == 1);

    return 0;
}