#include <bits/stdc++.h>

using namespace std;

int recursive_multiply(int a, int b){
    cout << a << " " << b << endl;
    if ((a == 0) or (b == 0)){
        return 0;
    }

    if (a == 1) return b;
    if (b == 1) return a;

    return (recursive_multiply(a>>1,b)<<1) + recursive_multiply((a-(a>>1<<1)),b);
}

int main(){
    assert(50*60 == recursive_multiply(50,60));
}
