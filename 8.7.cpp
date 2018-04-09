#include <bits/stdc++.h>
using namespace std;

int factorial(int n){
    int rv = 1;
    for (int i = 2; i <= n; i++) rv *= i;
    return rv;
}

void permute(list<vector<int> > &output, vector<int> &string, int prefix){
    if (prefix == string.size()){
        return;
    }
    if (prefix == string.size()-1){
        output.push_back(string);
        return;
    }
    for (int i = prefix; i < string.size(); i++){
        swap(string[prefix],string[i]);
        permute(output, string, prefix+1);
        swap(string[prefix],string[i]);
    }
    return;
}

int main(){
    vector<int> string = {1,2,3,4};
    list<vector<int>> permutations;
    permute(permutations, string, 0);
   
    assert(permutations.size() == factorial(string.size()));

    return 0;
}