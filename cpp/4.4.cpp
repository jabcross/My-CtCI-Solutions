#include <bits/stdc++.h>
using namespace std;

class BinaryTreeNode{
    public:
    int value;
    BinaryTreeNode* left, *right;
    BinaryTreeNode(int _value){
        value = _value;
        left = NULL;
        right = NULL;
    }
};


int get_height(BinaryTreeNode* root){
    if (!root) return 0;
    return max(get_height(root->left),get_height(root->right))+1;
}

bool is_balanced(BinaryTreeNode* root){
    if (!root) return true;
    return abs(get_height(root->left) - get_height(root->right)) <= 1;
}

int main(){
    BinaryTreeNode* root_a = new BinaryTreeNode(2);
    root_a->left = new BinaryTreeNode(1);
    root_a->right = new BinaryTreeNode(3);
 
    BinaryTreeNode* root_b = new BinaryTreeNode(2);
    root_b->left = new BinaryTreeNode(1);
    root_b->left->left = new BinaryTreeNode(3);

    assert(is_balanced(root_a));
    assert(!is_balanced(root_b));

    cout << "Tests passed" << endl;

    return 0;
}