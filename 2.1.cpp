#include <bits/stdc++.h>

using namespace std;

void remove_dups(list<int> &li){
    unordered_set<int> seen; // Storing seen values in hash
    for (auto item = li.begin(); item != li.end(); item++) {
        if (seen.count(*item)) item = --li.erase(item);
        else seen.insert(*item);
    }
}

int main(){
    list<int> l;
    l.push_back(1);
    l.push_back(3);
    l.push_back(2);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    remove_dups(l);

    int expected[4] = {1,3,2,4};
    auto it = l.begin();

    for (int i = 0; i < 4; i++, it++){
        assert((*it) == expected[i]);
    }

    cout << "Test passed" << endl;

}

// Follow-up: Sorting the linked list first (using the linked list version of
// mergesort), then doing a single pass to remove repeated values. This method 
// will destroy the original order, however.