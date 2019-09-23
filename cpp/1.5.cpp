#include <bits/stdc++.h>

using namespace std;

// Counts edits. A maximum of one may happen.
// Runtime: O(n)
bool distance_le_one(string a, string b){
    int len_a, len_b;
    len_a = a.size();
    len_b = b.size();
    if (abs(len_a - len_b) > 1) return false;

    if (len_a == len_b){
        bool changed = false;
        for (int i = 0; i < len_a; i++){
            if (a[i] != b[i]) {
                if (changed) return false;
                changed = true;
            }
        }
    }
    else {
        string *bigger = &a;
        string *smaller = &b;
        int bigger_len = len_a;
        int offset = 0;
        if (len_a < len_b){
            swap(bigger, smaller);
            bigger_len = len_b;
        }
        for (int i = 0; i < bigger_len; i++){
            if ((*smaller)[i] != (*bigger)[i+offset]){
                if (offset > 0) return false;
                offset = 1;
                i--;
            }
        }
    }
    return true;
}

int main(){

    assert(distance_le_one("Hello","Hi") == false);
    assert(distance_le_one("Hello","Hell") == true);
    assert(distance_le_one("Hello","Hel") == false);
    assert(distance_le_one("Hello","Jello") == true);
    assert(distance_le_one("Hello","Jelly") == false);
    cout << "Tests passed." << endl;
    return 0;
}