// Group Anagram

#include <bits/stdc++.h>

using namespace std;

template <typename T>
ostream& operator<<(ostream& stream, vector<T> &vec){
    stream << '[';
    for (int i = 0; i < vec.size(); i++) {
        stream << vec[i];
        if (i < vec.size()-1) stream <<", ";
    }
    stream << ']';
    return stream;
}

void group_anagrams(vector<string> &vec){
    auto tmp = vector<pair<string,string>>();
    for (auto i: vec) {
        string sorted = i;
        sort(sorted.begin(),sorted.end());
        tmp.push_back(make_pair(sorted,i));
    }
    sort(tmp.begin(),tmp.end());
    for (int i = 0; i < vec.size(); i++) vec[i] = tmp[i].second;
}

bool test_grouping(vector<string> vec){
    unordered_set<string> visited;
    string current = "";
    for (auto i: vec){
        string sorted = i;
        sort(sorted.begin(), sorted.end());
        if (sorted != current and visited.count(sorted)) return false;
        current = sorted;
        visited.insert(sorted);
    }
    return true;
}

int main(){
    vector<string> a = {"abc","def","cba","fed"};
    assert(!test_grouping(a));    
    group_anagrams(a);
    assert(test_grouping(a));
}