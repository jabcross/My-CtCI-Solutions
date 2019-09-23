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

void weave(list<int> a, list<int> b, list<list<int> > &target){
    if (a.empty()) {
        target.push_front(b);
        return;
    }
    if (b.empty()) {
        target.push_front(a);
        return;
    }
    auto a_head = a.front();
    a.pop_front();
    list<list<int> > tmp;
    weave(a,b,tmp);
    for (auto &i: tmp) i.push_front(a_head);
    target.splice(target.end(), tmp);

    tmp.clear();
    a.push_front(a_head);
    auto b_head = b.front();
    b.pop_front();

    weave(a,b, tmp);
    for (auto &i: tmp) i.push_front(b_head);
    
    target.splice(target.end(),tmp);
}

void weave_lists(list<list<int>> &l, list<list<int>> &r, list<list<int> > &target){
    list<list<int> > tmp;
    for (auto i: l){
        for (auto j: r){
            tmp.clear();
            weave(i,j,tmp);
            target.splice(target.end(),tmp);
        }
    }
    return;
}

void get_possible_source_arrays(BinaryTreeNode* root, list<list<int> > &target){
    if (!root) {
        target.push_front(list<int>());
        return;
    }
    list<list<int> > tmp_a, tmp_b, tmp_c;
    get_possible_source_arrays(root->left, tmp_a);
    get_possible_source_arrays(root->right, tmp_b);

    weave_lists(tmp_a, tmp_b, tmp_c);
    for (auto &i: tmp_c) i.push_front(root->value);
    target.splice(target.end(),tmp_c);
    return;
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

    list<list<int> > output;
    get_possible_source_arrays(refs[3], output);

    for (auto i: output){
        cout << "( ";
        for (auto j: i){
            cout << j << " ";
        }
        cout << ")" << endl;
    }
    return 0;
}