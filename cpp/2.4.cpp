#include <bits/stdc++.h>
using namespace std;

void partition(list<int> &i_list, int value){
    list<int> l_part, r_part;
    while (!i_list.empty()){
        if (i_list.front() < value){
            l_part.splice(l_part.end(), i_list, i_list.begin());
        }
        else {
            r_part.splice(r_part.end(), i_list, i_list.begin());
        }
    }
    i_list.splice(i_list.end(),l_part);
    i_list.splice(i_list.end(),r_part);
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

int main(){

    vector<int> my_vec = {5,1,6,2,7,3,8,4,9};
    vector<int> test_vec = {1,2,3,4,5,6,7,8,9};

    list<int> my_list (my_vec.begin(), my_vec.end());
    list<int> test_list (test_vec.begin(), test_vec.end());

    partition(my_list, 5);

    assert(cmp_lists(my_list, test_list));

    cout << "Test passed" << endl;

    return 0;
}