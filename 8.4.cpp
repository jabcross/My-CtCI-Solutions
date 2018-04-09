#include <bits/stdc++.h>
using namespace std;

void power_set(list<unordered_set<int>> &output, unordered_set<int> &_set){
    if (_set.empty()){
        output.push_back(unordered_set<int>());
        return;
    };
    list<unordered_set<int>> without;
    int first = *(_set.begin());
    _set.erase(_set.begin());
    power_set(without, _set);
    _set.insert(first);
    list<unordered_set<int>> with = without;
    for (auto &i: with) i.insert(first);
    output.splice(output.end(), without);
    output.splice(output.end(), with);
}

int main(){
    list<unordered_set<int>> output;
    unordered_set<int> _set = {1,2,4,5,6};
    power_set(output, _set);
    for (auto i: output){
        for (auto j: i){
            cout << j << ", ";
        }
        cout << endl;
    }
    cout << "Size: " << output.size() << endl;
}