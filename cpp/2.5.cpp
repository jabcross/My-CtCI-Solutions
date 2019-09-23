#include <bits/stdc++.h>
using namespace std;

template <typename T>
using list_iter = typename list<T>::iterator;

void sum_with_carry(list_iter<int> a_i,
                    list_iter<int> b_i,
                    list<int>&     a,
                    list<int>&     b,
                    list<int>&     c,
                    int            carry) {
    int sum = carry;
    if (a_i != a.end()) sum += *a_i, a_i++;
    if (b_i != b.end()) sum += *b_i, b_i++;
    c.push_back(sum % 10);
    if (a_i == a.end() and b_i == b.end()) return;
    sum_with_carry(a_i, b_i, a, b, c, sum / 10); // tail recursion
}

list<int> sum_lists(list<int> a, list<int> b) {
    list<int> c;
    sum_with_carry(a.begin(),b.begin(),a,b,c,0);
    return c;
}

bool cmp_lists(const list<int> &a, const list<int> &b){
    auto iter_a = a.begin(), iter_b = b.begin();
    while (true){
        if ((iter_a == a.end()) != (iter_b == b.end())){
            return false; // different sizes
        }
        if (iter_a == a.end()){
            return true;
        }
        if (*iter_a != *iter_b) return false;
        iter_a ++;
        iter_b ++;
    }
}

int main() {
    int a[3] = {3,2,1};
    int b[3] = {8,7,6};
    int c[4] = {1,0,8};
    list<int> list_a (a,a+3);
    list<int> list_b (b,b+3);
    list<int> test_c (c,c+3);

    list<int> list_c = sum_lists(list_a,list_b);
    assert(cmp_lists(list_c,test_c));

    cout << "Tests passed" << endl;
}

// Follow-up: Same, but do head recursion instead of tail recursion. Pad
// smallest addend with zeros until they're the same size. Append new digits on
// beginning of new linked list instead of on ending.