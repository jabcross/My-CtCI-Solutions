// Sparse search

#include <bits/stdc++.h>

using namespace std;

int find_sparse(vector<string> &vec, string s, int l, int r){
    assert (s != "");
    if (l + 1 == r) {
        if (vec[l] == s) return l;
        return -1;
    }
    if (l == r) return -1;
    int m = (l + r) / 2;
    int next_word = m;
    while (true){
        if (vec[next_word] == ""){
            next_word++;
        }
        else if (next_word == r) return find_sparse(vec, s, l, m);
        else if (vec[next_word] != "") break;
    } 
    if (vec[next_word] == s) return next_word;
    if (vec[next_word] > s) return find_sparse(vec, s, l, m);
    if (vec[next_word] < s) return find_sparse(vec, s, next_word + 1, r);
}

int main(){
    vector<string> inp = {"at","","","","ball","","","car","","","dad","",""};
    assert(find_sparse(inp, "ball", 0, inp.size())==4);
    assert(find_sparse(inp, "at", 0, inp.size())==0);
    assert(find_sparse(inp, "car", 0, inp.size())==7);
    assert(find_sparse(inp, "plane", 0, inp.size())==-1);
}