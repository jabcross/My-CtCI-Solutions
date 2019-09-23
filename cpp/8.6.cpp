#include <bits/stdc++.h>
using namespace std;

int hanoi(stack<int> &from, stack<int> &buffer, stack<int> &target, int depth){
    if (depth <= 0) return 0;
    int rv = hanoi(from,target,buffer,depth-1);
    target.push(from.top());
    from.pop();
    rv += 1;
    rv += hanoi(buffer,from,target,depth-1);
    return rv;
}

int main(){
    stack<int> a,b,c;
    for (int i: {4,3,2,1}) a.push(i);
    assert(hanoi(a,b,c,4)==15);
    return 0;
}
