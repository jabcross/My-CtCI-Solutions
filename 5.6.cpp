#include <bits/stdc++.h>
using namespace std;

int distance (int x, int y){
    int acc = 0;
    int diff = x ^ y;
    while (diff != 0){
        acc += diff & 1;
        diff >>= 1;
    }
    return acc;
}

int main(){
    assert(distance(29,15) == 2);
    cout << "Test passed" << endl;
    return 0;
}
