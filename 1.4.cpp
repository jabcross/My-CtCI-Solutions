#include <bits/stdc++.h>

using namespace std;

// Counts chars. A maximum of one may have an odd number of occurrences.
// Runtime: O(n)
bool is_palindrome_permutation(string str){
    int chars[256];
    for (int i = 0; i < 256; i++) chars[i] = 0;

    for (auto chr : str){

        // We can ignore spaces here, if desired.
        // if (chr == ' ') continue;

        chars[chr] ++;
    }

    bool has_odd = false;

    for (int i = 0; i < 256; i++){
        if (chars[i] % 2){
            if (has_odd) return false;
            has_odd = true;
        }
    }
    return true;
}

int main(){

    assert(is_palindrome_permutation("aaaab"));
    assert(is_palindrome_permutation("aaaabb"));
    assert(is_palindrome_permutation(""));
    assert(is_palindrome_permutation("ab") == false);
    cout << "Tests passed." << endl;
    return 0;
}