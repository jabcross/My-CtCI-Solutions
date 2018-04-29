#include <bits/stdc++.h>

using namespace std;

int _negate (int a){
    int acc = 0;
    int sign;
    if (a < 0) {
        sign = -1;
    }
    else sign = 1;
    int increase = sign;
    while (a + acc != 0){
        int diffsigns = (a > 0) != (a + increase > 0);
        if (a + increase != 0 and diffsigns){
            increase = sign;
        }
        acc += increase;
        increase += increase;
    }
    return acc;
}

int subtract(int a, int b){
    return a + _negate(b);
}

int multiply(int a, int b){
    int big = max(a,b), small = min(a,b);
    int sign = 1;
    if (big < 0) sign = _negate(sign), big = _negate(big);
    if (small < 0) sign = _negate(sign), small = _negate(small);
    int acc = 0;
    for (int i = 0; i < small; i++) acc += big;
    if (sign < 0) acc = _negate(acc);
    return acc;
}

int divide(int a, int b){
    int big = max(a,b), small = min(a,b);
    int sign = 1;
    if (big < 0) sign = _negate(sign), big = _negate(big);
    if (small < 0) sign = _negate(sign), small = _negate(small);

    int acc = 0;
    while (a >= 0) a = subtract(a,b), acc += 1;
    acc = subtract(acc,1);

    if (sign < 0) acc = _negate(acc);
    return acc;
}

int main(){
    assert(_negate(10)==-10);
    assert(_negate(-10)==10);
    assert(_negate(0)==0);
    assert(subtract(10,5)==5);
    assert(multiply(-10,5)==-50);
    assert(divide(13,5)==2);
}