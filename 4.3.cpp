#include <bits/stdc++.h>
using namespace std;

class BinaryTreeNode{
    public:
    int value;
    BinaryTreeNode* left, *right;
};


void create_lls_recurse(BinaryTreeNode* root, vector<list<int> > &lists, int depth){
    if (!root) return;
    while (lists.size() <= depth) lists.push_back(list<int>());
    lists[depth].push_back(root->value);
    create_lls_recurse(root->left, lists, depth + 1);
    create_lls_recurse(root->right, lists, depth + 1);
}

vector<list<int> > create_lls(BinaryTreeNode* root){
    vector<list<int> > lists;
    create_lls_recurse(root, lists, 0);
    return lists;
}

int main(){
    BinaryTreeNode* root = new BinaryTreeNode();
    root->value = 2;
    root->left = new BinaryTreeNode();
    root->left->value = 1;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right = new BinaryTreeNode();
    root->right->value = 3;
    root->right->left = NULL;
    root->right->right = NULL;
 
    auto lists = create_lls(root);

    assert(lists[0].front() == 2);
    assert(lists[1].front() == 1);
    assert(lists[1].back() == 3);

    cout << "Tests passed" << endl;

    return 0;
}