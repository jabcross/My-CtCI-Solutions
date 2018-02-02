#include <bits/stdc++.h>
using namespace std;

bool is_palindrome(const list<int> &li){
    auto l = li.begin();
    auto r = li.end();

    if (l == li.end()) return true;
    r--;

    while (true){
        if (l == li.end()){
            return true;
        }
        if (l == r){
            return true;
        }
        auto l_next = l;
        l_next++;
        if (l_next == r){
            return *l == *r;
        }
        if (*l != *r) return false;
        l++;
        r--;
    }
}

int main(){

    int a[5] = {1,2,3,4,5};
    int b[5] = {1,2,3,2,1};
    int c[4] = {1,2,2,1};
    int d[4] = {1,2,3,1};

    list<int> list_a (a,a+5);
    list<int> list_b (b,b+5);
    list<int> list_c (c,c+4);
    list<int> list_d (d,d+4);
    list<int> list_e ;

    assert(is_palindrome(list_a) == false);
    assert(is_palindrome(list_b));
    assert(is_palindrome(list_c));
    assert(is_palindrome(list_d) == false);
    assert(is_palindrome(list_e));

    cout << "Tests passed" << endl;

    return 0;
}