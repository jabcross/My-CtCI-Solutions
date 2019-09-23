#include <bits/stdc++.h>

using namespace std;

int my_max(int i, int j){
    return (abs(i-j) + i + j)/2;
}

int main(){
    assert(my_max(5,4) == 5);
    assert(my_max(4,5) == 5);
    assert(my_max(4,4) == 4);
}
