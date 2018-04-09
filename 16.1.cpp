#include<bits/stdc++.h>

void swap(int& a, int& b){
    a = a^b;
    b = a^b;
    a = a^b;
}

int main(){
    int a = 5;
    int b = 7;
    swap(a,b);
    assert((b == 5) and (a == 7));
}
