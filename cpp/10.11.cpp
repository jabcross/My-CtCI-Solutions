#include <bits/stdc++.h>

using namespace std;

void peak_and_vallify(vector<int> &vec){
    for (int i = 0; i < vec.size()-1; i++){
        if (i %2 == 0){
            // this should be a peak.
            if (vec[i] < vec[i+1]) swap(vec[i],vec[i+1]);
        }
        else if (i % 2 == 1){
            // this should be a valley.
            if (vec[i] > vec[i+1]) swap(vec[i],vec[i+1]);            
        }
    }
}

bool is_peakvalleyfied(vector<int> &vec){
    if (vec.size() <= 1) return true;
    for (int i = 0; i < vec.size(); i++){
        if (i%2 == 0){
            // peak
            if (i > 0 and vec[i] < vec[i-1]) return false;
            if (i < vec.size()-1 and vec[i] < vec[i+1]) return false;
        }
        else if (i%2 == 1){
            // valley
            if (i > 0 and vec[i] > vec[i-1]) return false;
            if (i < vec.size()-1 and vec[i] > vec[i+1]) return false;
        }
    }
    return true;
}

int main(){
    vector<int> input = {5,3,1,2,3};
    peak_and_vallify(input);
    assert(is_peakvalleyfied(input));
}