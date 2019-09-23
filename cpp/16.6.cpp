#include <bits/stdc++.h>

using namespace std;

int smallestDifference (vector<int> const& ra, vector<int> const& rb){
    int _min = INT32_MAX;
    vector<int> a = ra, b = rb;
    int ai = 0, bi = 0;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    while (true){
        if (a[ai] - b[bi] >= 0) _min = min(_min, a[ai] - b[bi]);
        if (a[ai] < b[bi]){
            ai++;
            if (ai >= a.size()) break;
        }
        else if (a[ai] > b[bi]){
            bi++;
            if (bi >= b.size()) break;
        } 
    }
    return _min;
}

int main(){
    vector<int> a = {1, 3, 15, 11, 2};
    vector<int> b = {23, 127, 235, 19, 8};
    assert(smallestDifference(a,b) == 3);
}