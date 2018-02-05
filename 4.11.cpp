#include <bits/stdc++.h>
using namespace std;

class BST {
   public:
    class BST_Node {
        int       value, size_left, size_right;
        BST_Node *left, *right;

       public:
        BST_Node(int val) {
            value = val, size_left = size_right = 0;
            left = right = 0;
        }
        bool insert(int _value) {
            if (value == _value) return false;
            if (value < _value) {
                if (right) {
                    if (right->insert(_value)) size_right++;
                } else {
                    right = new BST_Node(_value);
                    size_right++;
                }
            }
            if (value > _value) {
                if (left) {
                    if (left->insert(_value)) size_left++;
                } else {
                    left = new BST_Node(_value);
                    size_left++;
                }
            }
        }
        bool find(int _value) {
            if (value == _value) return true;
            if (_value < value) {
                if (left) return left->find(_value);
                return false;
            }
            if (_value > value) {
                if (right) return right->find(_value);
                return false;
            }
        }
        bool remove(int _value){
            if (value == _value){
                if (!left and right){
                    value = right->value;
                    left = right->left;
                    auto tmp = right;
                    right = right->right;
                    size_right --;
                    delete tmp;
                    return true;
                }
                if (left and !right){
                    value = left->value;
                    right = left->right;
                    auto tmp = left;
                    left = left->left;
                    size_left --;
                    delete tmp;
                    return true;
                }
                if (!left and !right){
                    return true;
                }
                if (size_right > size_left){
                    value = right->value;
                    if (size_right > 1){
                        right->remove(value);
                        size_right --;
                    }
                    else {
                        delete right;
                        right = NULL;
                    }
                    return true;
                }
                else{
                    value = left->value;
                    if (size_left > 1){
                        left->remove(value);
                        size_left --;
                    }
                    else {
                        delete left;
                        left = NULL;
                    }
                    return true;
                }

            }
            if (value < _value){
                if (!right) return false;
                if (right->remove(_value)){
                    size_right --;
                    return true;
                }
                return false;
            }
            if (value > _value){
                if (!left) return false;
                if (left->remove(_value)){
                    size_left --;
                    return true;
                }
                return false;
            }
        }
        BST_Node* randomNode(){
            double total = 1 + size_left + size_right;
            double this_chance = 1;
            double left_chance = size_left;
            double right_chance = size_right;
            double random = (double)rand() / RAND_MAX;

            if (left and (random < left_chance / total)){
                return left->randomNode();
            }
            if (right and (random < (right_chance + left_chance) / total)){
                return right->randomNode();
            }
            return this;
        }
    };


    BST (){
        root = NULL;
    }

    bool insert(int value){
        if (root) return root->insert(value);
        root = new BST_Node(value);
        return true;
    }
    bool find(int value){
        if (root) return root->find(value);
        return false;
    }
    bool remove(int value){
        if (root) return root->remove(value);
        return false;
    }
    BST_Node* randomNode(){
        if (root) return root->randomNode();
        return NULL;
    }
    private:
    BST_Node* root;
};

int main(){
    return 0;
}