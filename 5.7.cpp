#include <bits/stdc++.h>
using namespace std;

int sieve = (0b01010101010101010101010101010101);

int swap (int x){
    int evens = (x & sieve);
    int odds = (x & ~sieve);
    return (evens << 1) | (odds >> 1);
}

int main(){
    assert(swap(0b1110010011100100) == 0b1101100011011000);
    cout << "Test passed" << endl;
    return 0;
}
