#include <bits/stdc++.h>
using namespace std;

int insert(int n, int m, int i, int j){
    int mask1 = (~0 >> i) << i;
    int mask2 = (~0 >> j) << j;
    int mask = ~(mask1 ^ mask2);
    return (n & mask)|(m << i);
}

void print(int x){
    for (int i = 0; i < 32; i++){
        cout << ((x>>(31-i)) & 1);
    }
}

int main(){

    int a = 0b10000000000;
    int b = 0b10011;
    print(a);
    cout << endl;
    print(b);
    cout << endl;
    print(insert(a,b,2,6));
    assert(insert(a,b,2,6) == 0b10001001100);

    return 0;
}