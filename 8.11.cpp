#include <bits/stdc++.h>
using namespace std;


struct pair_hash {
    size_t operator() (pair<int,int> p) const {
        auto a = hash<int>{}(p.first);
        auto b = hash<int>{}(p.second);
        return a ^ (b+3);
    }
};


int fit(int cents, int size, unordered_map<pair<int,int>,int,pair_hash> &memo){
    if (memo.find(make_pair(cents,size))!=memo.end()){
        return memo[make_pair(cents,size)];
    }
    if (size == 1) {
       return 1;
    }
    int rv = 0;
    if (cents >= size){
        rv += fit(cents-size,size,memo);
    }
    int smaller_size;
    if (size == 25) smaller_size = 10;
    else if (size == 10) smaller_size = 5;
    else if (size == 5) smaller_size = 1;
    rv += fit(cents, smaller_size,memo);
    memo[make_pair(cents,size)]=rv;
    return rv;
}

int main(){
    unordered_map<pair<int,int>,int,pair_hash> memo;
    cout << fit(26,25,memo) << endl;
    return 0;
}