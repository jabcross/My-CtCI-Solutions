// Not the optimal solution. There is a O(n) solution (where n is the max of the width and height of the matrix), while this solution is O(n^log2(3)).

#include <bits/stdc++.h>
using namespace std;

const pair<int,int> NONE = make_pair(-1,-1);

pair<int,int> find_on_matrix(vector<vector<int>> &m, int value, int x1, int y1, int x2, int y2){
    if (x2 <= x1 or y2 <= y1) return NONE;
    if (x2 == x1 + 1 and y2 == y1 + 1) {
        if (m[y1][x1] == value)
            return make_pair(y1,x1);
        else return NONE;
    }
    if (m[y1][x1] > value or m[y2-1][x2-1] < value) return NONE;
    int xm = (x1 + x2)/2;
    int ym = (y1 + y2)/2;
    pair<int,int> rv = find_on_matrix(m,value,x1,y1,xm,ym);
    if (rv != NONE){
        return rv;
    }
    rv = find_on_matrix(m,value,xm,ym,x2,y2);
    if (rv != NONE){
        return rv;
    }
    return find_on_matrix(m,value,xm,y1,x2,ym);
}

int main(){
    vector<vector<int>> m = {
        {1,2,3,4,5},{2,4,6,8,10},{3,6,9,12,15},{4,8,12,16,20},{5,10,15,20,15}
    };
    pair<int,int> pos = find_on_matrix(m,10,0,0,5,5);
    assert(pos == make_pair(4,1) or pos == make_pair(1,4));
    pos = find_on_matrix(m,11,0,0,5,5);
    assert(pos == NONE);
}