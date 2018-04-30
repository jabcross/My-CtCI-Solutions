#include <bits/stdc++.h>

using namespace std;

pair<int,int> get_hits_and_pseudohits(vector<int> guess, vector<int> solution){
    bitset<4> exists, hits, pseudohits;
    exists.reset(), hits.reset(), pseudohits.reset();
    for (int i = 0; i < 4; i++){
        exists.set(solution[i]);
        if (guess[i] == solution[i]) {
            hits.set(solution[i]);
        }
    }
    for (int i = 0; i < 4; i++){
        if(exists[guess[i]] and !hits[guess[i]]) pseudohits.set(guess[i]);
    }
    return make_pair(hits.count(),pseudohits.count());
}

int main(){
    vector<int> guess = {1,1,2,2};
    vector<int> solution = {2,1,0,3};
    auto rv = get_hits_and_pseudohits(guess,solution);
    cout << "hits: " << rv.first << " pseudohits: " << rv.second << endl;
    assert(rv == make_pair(1,1));
}