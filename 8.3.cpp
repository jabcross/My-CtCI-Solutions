#include <bits/stdc++.h>
using namespace std;

// If all numbers are distinct
int magic_index(vector<int> &array, int l, int r){
    if (l >= r) return -1;
    int m = (l+r)/2;
    if (array[m] == m) return m;
    if (array[m] > m){
        return magic_index(array, l, m);
    }
    else return magic_index(array, m, r);
}

// if not all numbers are distinct
int magic_index_indistinct(vector<int> &array, int l, int r){
if (l >= r) return -1;
    int m = (l+r)/2;
    if (array[m] == m) return m;
    int left = magic_index(array, l, min(array[m],m));
    if (left != -1) return left;
    return magic_index(array, max(array[m],m) + 1, r);
}

int main(){
    vector<int> test1 = {-5,-4,-3,3,4,5}; 
    assert(magic_index(test1,0,6)==3);

    vector<int> test2 = {1,2,2,3,4,4,5,6}; 
    assert(magic_index(test2,0,test2.size())==4);
}