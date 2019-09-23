#include <bits/stdc++.h>

using namespace std;

// Single pass.
// Runtime: O(n)
string compress(string str){
    int old_len = str.size();
    if (old_len == 0) return str;
    string new_string = "";
    char current = str[0];
    int count = 1;
    new_string.push_back(str[0]);
    for (int i = 1; i < old_len; i++){
        if (str[i] != current){
            new_string.append(to_string(count) + str[i]);
            current = str[i];
            count = 1;
        }
        else {
            count++;
        }
    }
    new_string.append(to_string(count));
    if (new_string.size() < old_len) return new_string;
    return str;
}   

int main(){
    assert("hello" == compress("hello"));
    assert(compress("aabcccccaaa") == "a2b1c5a3");
    cout << "Tests passed." << endl;
    return 0;
}