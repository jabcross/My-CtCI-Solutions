#include <bits/stdc++.h>
using namespace std;

int parens(list<string> &combinations, string &prefix, int n, int open){
    if ((n == 0) and (open == 0)){
        combinations.push_back(prefix);
    }
    if (n > 0){
        prefix += "(";
        parens(combinations, prefix, n-1, open+1);
        prefix.pop_back();
    }
    if (open > 0){
        prefix += ")";
        parens(combinations, prefix, n, open-1);
        prefix.pop_back();
    }
}

int main(){
    list<string> combinations;
    string prefix;
    parens(combinations, prefix, 3, 0);
    for (auto i: combinations)cout << i << endl;
}