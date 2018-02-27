#include <bits/stdc++.h>
using namespace std;

int triple_step(int n){
    if (n == 1) return 1;
    if (n == 2) return 2;
    if (n == 3) return 4;
    int curr = 3;
    int minus0 = 4;
    int minus1 = 2;
    int minus2 = 1;
    while (curr < n){
        int tmp = minus0 + minus1 + minus2;
        minus2 = minus1;
        minus1 = minus0;
        minus0 = tmp;
        curr++;
    }
    return minus0;
}

int main(){
    
    int ins[] = {1,2,3,4,5,6,7};
    int outs[] = {1,2,4,7,13,24,44};

    for (int i = 0; i < 7; i++) assert(outs[i] == triple_step(ins[i]));
    return 0;
}