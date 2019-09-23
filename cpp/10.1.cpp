// Sorted-merge

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

template<typename T>
void sorted_merge(vector<T> &a, vector<T> &b){
    assert(a.capacity() >= a.size() + b.size());
    int ra = a.size()-1;
    int rb = b.size()-1;
    for (int i = 0; i < b.size(); i++) a.push_back(0);
    int last = a.size() - 1;
    while (ra > -1 or rb > -1){
        if (rb == -1) break;
        if ((ra > -1) and (a[ra] > b[rb])){
            a[last] = a[ra];
            ra --;
            last --;
        }
        else {
            a[last] = b[rb];
            rb --;
            last --;
        }
        // cout << a << ' ' << ra << ' ' << rb <<  endl;
    }
}

int main(){
    vector<int> a = {1,3,5,7};
    a.reserve(10);
    vector<int> b = {2,4,6};
    vector<int> c = {1,2,3,4,5,6,7};
    sorted_merge(a,b);
    // cout << a << endl;
    for (int i = 0; i < a.size(); i++)
        assert(a[i] == c[i]);
    return 0;
}