#include <bits/stdc++.h>
using namespace std;

vector<int> generate_all_possible_lengths(int k, int shorter, int longer){
    vector<int> rv;
    for (int i = 0; i <= k; i++){
        rv.push_back(k*shorter + i * (longer-shorter));
    }
    return rv;
}

int main(){
    vector<int> test = {4,5,6};
    vector<int> rv = generate_all_possible_lengths(2,2,3);
    assert(test == rv);
}