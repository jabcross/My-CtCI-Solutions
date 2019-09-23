#include <bits/stdc++.h>
using namespace std;

bool get(int x, int pos){
    return (x >> pos) & 1;
}

int flip_bit_to_win(int x){
    int beginnings[32];
    int endings[32];
    for (int i = 0; i < 32; i++) beginnings[i] = endings[i] = 0;

    bool is_ones = false;
    int l = 0;
    for (int i = 0; i < 32; i++){
        if (get(x,i)){
            if (!is_ones){
                l = i;
                is_ones = true;
            }
        }
        else {
            if (is_ones){
                beginnings[l] = i - l;
                endings[i-1] = i - l;
                is_ones = false;    
            }
        }
    }
    if (get(x,31)){
        beginnings[l] = 32 - l;
        endings[31] = 32 - l;        
    }

    int maximum = 0;

    for (int i = 0; i < 32; i++){
        maximum = max(maximum, beginnings[i]);
        if (!get(x,i)){
            int acc = 0;
            if (i > 0) acc += endings[i-1];
            if (i < 31) acc += beginnings[i+1];
            acc += 1;
            maximum = max(maximum,acc);
        }
    }
    return maximum;
}

int main(){

    assert(flip_bit_to_win(0b11011101111) == 8);
    assert(flip_bit_to_win(0b11001100111) == 4);
    assert(flip_bit_to_win(~0) == 32);
    assert(flip_bit_to_win(0) == 1);

    return 0;
}