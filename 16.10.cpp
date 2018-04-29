#include <bits/stdc++.h>
using namespace std;

int year_with_most_living_people(vector<pair<int, int>>& v) {
    vector<int> births;
    vector<int> deaths;
    for (auto i : v) {
        births.push_back(i.first);
        deaths.push_back(i.second + 1);
    }
    sort(births.begin(),births.end());
    sort(deaths.begin(),deaths.end());
    int i = 0, j = 0;
    int lives = 0;
    pair<int,int> m = make_pair(0,0);
    while(i < births.size() and j < deaths.size()){
        if (births[i] < deaths[j]){
            lives++;
            m = max(m,make_pair(lives,births[i]));
            i++;
        }
        else if (births[i] > deaths[j]){
            lives --;
            j++;
        }
        else {
            i++;
            j++;
        }
    }
    return m.second;
}

int main() {
    vector<pair<int,int>> v = {{1,6},{2,5},{3,4}};
    int rv = year_with_most_living_people(v);
    assert(rv == 3 or rv == 4);
}