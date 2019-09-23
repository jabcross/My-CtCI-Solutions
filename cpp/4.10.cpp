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

bool isSame(BinaryTreeNode* t1, BinaryTreeNode* t2) {
    if ((t1 == NULL) and (t2 == NULL)) return true;
    if (!t1 != !t2) return false;
    return (t1->value == t2->value) and isSame(t1->left, t2->left) and
           isSame(t1->right, t2->right);
}

bool isSubtree(BinaryTreeNode* t1, BinaryTreeNode* t2){
    queue<BinaryTreeNode*> q;
    q.push(t1);
    while (!q.empty()){
        if (isSame(q.front(),t2)) return true;
        if (q.front()){
            q.push(q.front()->left);
            q.push(q.front()->right);
        }
        q.pop();
    }
    return false;
}

int main() {
    BinaryTreeNode* refs[7];
    refs[3] = new BinaryTreeNode(3, NULL);
    refs[1] = refs[3]->addLeftNode(1);
    refs[5] = refs[3]->addRightNode(5);
    refs[0] = refs[1]->addLeftNode(0);
    refs[2] = refs[1]->addRightNode(2);
    refs[4] = refs[5]->addLeftNode(4);
    refs[6] = refs[5]->addRightNode(6);

    assert(isSubtree(refs[3],refs[1]));
    assert(!isSubtree(refs[1],refs[3]));

    cout << "Test passed" << endl;

    return 0;

}