#include <bits/stdc++.h>
using namespace std;

class BinaryTreeNode{
    public:
    int value;
    BinaryTreeNode* left, *right;
};

BinaryTreeNode* make_bst(vector<int>&array, int begin, int end){
    if (begin >= end) return NULL;
    BinaryTreeNode* root = new BinaryTreeNode();
    int middle = (begin + end)/2;
    root->value = array[(begin+end)/2];
    root->left = make_bst(array, begin, middle);
    root->right = make_bst(array,middle+1,end);
    return root;
}

int get_height(BinaryTreeNode* root){
    if (!root) return 0;
    return max(get_height(root->left),get_height(root->right))+1;
}

int main(){
    vector<int> test = {1,2,3,4,5,6,7,8};

    int min_height = ceil(log2(test.size())) + 1;

    auto bst = make_bst(test,0,test.size());

    assert (get_height(bst) == min_height);

    cout << "Test passed" << endl;

    return 0;
}