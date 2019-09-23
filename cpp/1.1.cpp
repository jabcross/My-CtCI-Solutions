#include <bits/stdc++.h>

using namespace std;

// Uses array of bools to check if the character has been seen before.
// Runtime: O(len(str))
bool is_unique(string str){
    bitset<256> chars;
    for (auto chr: str){
        if (chars[chr]){
            return false;
        }
        chars[chr] = true;
    }
    return true;
}

int main(){
    assert(is_unique("") == true);
    assert(is_unique("a") == true); 
    assert(is_unique("abcde") == true);
    assert(is_unique("abcba") == false);
    cout << "Tests passed." << endl;
    return 0;
}