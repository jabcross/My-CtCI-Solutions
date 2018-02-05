#include <bits/stdc++.h>
using namespace std;

class BinaryTreeNode {
   public:
    int             value;
    BinaryTreeNode *left, *right;
    BinaryTreeNode(int _value) {
        value = _value;
        left  = NULL;
        right = NULL;
    }
};

tuple<bool, int, int> validate_bst(BinaryTreeNode* root) {
    if (!root) return make_tuple(true, INT_LEAST32_MAX, INT_LEAST32_MIN);
    auto val_left  = validate_bst(root->left);
    auto val_right = validate_bst(root->right);
    int minimum = min(root->value, min(get<1>(val_left), get<1>(val_right)));
    int maximum = max(root->value, max(get<2>(val_left), get<2>(val_right)));

    int validation = get<0>(val_left) and get<0>(val_right) and
                     (get<2>(val_left) < root->value) and
                     (get<1>(val_right) > root->value);
    return make_tuple(validation, minimum, maximum);
}

int main() {
    BinaryTreeNode* root_a = new BinaryTreeNode(2);
    root_a->left           = new BinaryTreeNode(1);
    root_a->right          = new BinaryTreeNode(3);

    BinaryTreeNode* root_b = new BinaryTreeNode(1);
    root_b->left           = new BinaryTreeNode(2);
    root_b->left->left     = new BinaryTreeNode(3);

    assert(get<0>(validate_bst(root_a)));
    assert(!get<0>(validate_bst(root_b)));

    cout << "Tests passed" << endl;

    return 0;
}