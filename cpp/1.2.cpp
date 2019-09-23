#include <bits/stdc++.h>

using namespace std;

// Uses array of ints to count number of each character in each string.
// Runtime: O(n), where n equals the lengths of both a and b.
bool is_permutation(string a, string b){
    if (a.size() != b.size()) return false;
    int chars_a[256], chars_b[256];
    for (int i = 0; i < 256; i++) chars_a[i] = chars_b[i] = 0;
    for (auto chr: a){
        chars_a[chr] += 1;
    }
    for (auto chr: b){
        chars_b[chr] += 1;
    }
    for (int i = 0; i < 256; i++){
        if (chars_a[i] != chars_b[i]) return false;
    }
    return true;
}

int main(){
    assert(is_permutation("","") == true);
    assert(is_permutation("avocado","adocavo") == true);
    assert(is_permutation("avocado","banana") == false);
    assert(is_permutation("avocado","abanana") == false);
    cout << "Tests passed." << endl;
    return 0;
}