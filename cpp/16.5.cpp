#include <bits/stdc++.h>

using namespace std;

// The number of trailing zeros of a number is the number of times this number
// can be divided by 10, which is the min of the number of 5 factors and 2
// factors. A factorial number will always have more 2 factors than 5 factors,
// so the answer is just the number of 5 factors. This itself is n / 5 + n / 25
// + n/125 ... Which is easy enough to compute.

// We should be careful with the expected limits on the input. The variable
// f in the function might overflow if i > MAX_INT/5.

int num_trailing_zeros_fac(int i){
    int f = 5;
    int acc = 0;
    while (f <= i){
        acc += i / f;
        f *= 5;
    }
    return acc;
}

int main(){
    assert(num_trailing_zeros_fac(4) == 0); // 24
    assert(num_trailing_zeros_fac(5) == 1); // 12e1
    assert(num_trailing_zeros_fac(11) == 2); // 399168e2
    assert(num_trailing_zeros_fac(27) == 6); // 10888869450418352160768e6
}