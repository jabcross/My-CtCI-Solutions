#include <bits/stdc++.h>
using namespace std;

class BinaryTreeNode {
   public:
    int             value;
    BinaryTreeNode *left, *right, *parent;
    BinaryTreeNode(int _value, BinaryTreeNode* _parent) {
        value  = _value;
        left   = NULL;
        right  = NULL;
        parent = _parent;
    }
    BinaryTreeNode* addRightNode(int _value) {
        right = new BinaryTreeNode(_value, this);
        return right;
    }
    BinaryTreeNode* addLeftNode(int _value) {
        left = new BinaryTreeNode(_value, this);
        return left;
    }
};

BinaryTreeNode* successor(BinaryTreeNode* root) {
    if (!root) return NULL;
    // if has right child
    if (root->right) {
        auto scout = root->right;
        while (scout->left != NULL) { scout = scout->left; }
        return scout;
    }
    // if doesn't have right child
    else {
        auto scout = root;
        while (scout->parent and (scout->parent->right == scout)) {
            scout = scout->parent;
        }
        return (scout->parent);
    }
}

int main() {
    BinaryTreeNode *refs[10];
    refs[7] = new BinaryTreeNode(7, NULL);
    refs[1] = refs[7]->addLeftNode(1);
    refs[3] = refs[1]->addRightNode(3);
    refs[2] = refs[3]->addLeftNode(2);
    refs[5] = refs[3]->addRightNode(5);
    refs[4] = refs[5]->addLeftNode(4);
    refs[6] = refs[5]->addRightNode(7);
    refs[8] = refs[7]->addRightNode(8);
    refs[9] = NULL;

    for (int i: {1,2,3,4,5,6,7,8}){
        assert(successor(refs[i]) == refs[i+1]);
    }

    cout << "Tests passed" << endl;

    return 0;
}