#include <bits/stdc++.h>

using namespace std;

bool is_rotation(string s1, string s2){
    if (s1.size() != s2.size()) return false;

    string s1x2 = s1 + s1;
    if (s1x2.find(s2) != string::npos){
        return true;
    }
    return false;
}

int main(){
    assert(is_rotation("asdf","sdfa"));
    assert(!is_rotation("asdf","sdf"));
    assert(!is_rotation("asdf","sdfas"));

    cout << "Test Passed" << endl;
}