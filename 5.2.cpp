#include <bits/stdc++.h>
using namespace std;

string to_binary_representation(double x){
    if (x == 1.0) return "1";
    if (x == 0.0) return "0";
    string rv = "0.";
    int count = 30;
    while (count){
        if (x == 0.0) return rv;
        if (x >= 0.5){
            rv += "1";
            x = (x - 0.5) * 2;
        }
        else {
            rv += "0";
            x = x * 2;
        }
    }
    return "ERROR.";
}

int main(){

    assert(to_binary_representation(0.5) == "0.1");
    assert(to_binary_representation(0.0) == "0");
    assert(to_binary_representation(1.0) == "1");
    assert(to_binary_representation(0.25) == "0.01");
    assert(to_binary_representation(0.75) == "0.11");

    return 0;
}