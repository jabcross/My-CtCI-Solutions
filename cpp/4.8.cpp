#include <bits/stdc++.h>
using namespace std;

// If we have parent references in our nodes, we can calculate each depth, find
// // an ancestor of the deepest node that has the same depth as the other node,
// // and iterate both upwards at the same time until a common ancestor is
// found.

// If not, we need a recursive function that finds wether a node's subtree
// contains these two nodes.

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

typedef BinaryTreeNode BTN;

struct RetVal {
    BTN* result;
    bool a, b;
};

RetVal has_nodes(BTN* root, BTN* a, BTN* b) {
    if (!root) return {NULL,false,false};
    RetVal l = has_nodes(root->left, a, b);
    if (l.result) return l;
    if ((l.a and (root==b)) or (l.b and (root==a))) return {root, true, true};
    RetVal r = has_nodes(root->right, a, b);
    if (r.result) return r;
    if ((r.a and (root==b)) or (r.b and (root==a))) return {root, true, true};
    if ((l.a and r.b) or (l.b and r.a)){
        return {root,true,true};
    }
    return {NULL,l.a or r.a or (root==a), l.b or r.b or (root==b)};
}

int main(){
    BTN *refs[5];

    refs[0] = new BinaryTreeNode(0,NULL);
    refs[1] = refs[0]->addLeftNode(1);
    refs[2] = refs[1]->addLeftNode(2);
    refs[3] = refs[1]->addRightNode(3);
    refs[4] = refs[3]->addLeftNode(3); 

/* 
            0
           /
          1 <-- common ancestor
         / \
       [2]  3
             \
             [4]
 */

    assert(has_nodes(refs[0],refs[2],refs[4]).result == refs[1]);
    cout << "Test passed" << endl;

    return 0;
}
    
