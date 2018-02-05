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

list<list<int>> weave(list<int> a, list<int> b){
    auto rv = list<list<int> >();
    if (a.empty()) {
        rv.push_front(b);
        return rv;
    }
    if (b.empty()) {
        rv.push_front(a);
        return rv;
    }
    auto a_head = a.front();
    a.pop_front();
    auto x = weave(a,b);
    for (auto &i: x) i.push_front(a_head);
    a.push_front(a_head);
    auto b_head = b.front();
    b.pop_front();
    auto y = weave(a,b);
    for (auto &i: y) i.push_front(b_head);

    rv.splice(rv.end(),x);
    rv.splice(rv.end(),y);
    return rv;
}

list<list<int>> weave_lists(list<list<int>> l, list<list<int>> r){
    auto rv = list<list<int>>();
    for (auto i: l){
        for (auto j: r){
            rv.splice(rv.end(),weave(i,j));
        }
    }
    return rv;
}

list<list<int> > get_possible_source_arrays(BinaryTreeNode* root){
    if (!root) {
        list<list<int>> rv = list<list<int>>();
        rv.push_front(list<int>());
        return rv;
    }
    auto l = get_possible_source_arrays(root->left);
    auto r = get_possible_source_arrays(root->right);

    auto rv = weave_lists(l,r);
    for (auto &i: rv) i.push_front(root->value);
    return rv;
}

int main(){
    BinaryTreeNode *refs[7];
    refs[3] = new BinaryTreeNode(3,NULL);
    refs[1] = refs[3]->addLeftNode(1);
    refs[5] = refs[3]->addRightNode(5);
    refs[0] = refs[1]->addLeftNode(0);
    refs[2] = refs[1]->addRightNode(2);
    refs[4] = refs[5]->addLeftNode(4);
    refs[6] = refs[5]->addRightNode(6);

    auto rv = get_possible_source_arrays(refs[3]);

    for (auto i: rv){
        cout << "( ";
        for (auto j: i){
            cout << j << " ";
        }
        cout << ")" << endl;
    }
    return 0;
}