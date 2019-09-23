#include <bits/stdc++.h>
using namespace std;

typedef pair<double, double> point;
typedef pair<point, point>   segment;

void printpoint(point p){
    cout << p.first << " " << p.second << endl;
}

pair<point, bool> single_intersection(segment a, segment b) {
    bool a_vert = a.first.first == a.second.first;
    bool b_vert = b.first.first == b.second.first;
    
    if (a_vert and b_vert) {
        // both vertical
        return make_pair(make_pair(0, 0), false);
    }
    if (a_vert) {
        // a is vertical, swap so b is vertical instead
        swap(a, b);
    }
    double a_slope =
        (a.second.second - a.first.second) / (a.second.first - a.first.first);
    double a_offset = a_slope * a.first.first - a.first.second;
    point  intersection;
    if (b_vert) {
        intersection.first  = b.first.first;
        intersection.second = intersection.first * a_slope + a_offset;
    }
    else {
        double b_slope = (b.second.second - b.first.second) / (b.second.first - a.first.first);
        if (b_slope == a_slope) return make_pair(make_pair(0,0),false);
        double b_offset = b_slope * b.first.first - b.first.second;
        intersection.first = (b_offset - a_offset)/(b_slope - a_slope);
        intersection.second = a_slope * intersection.first + a_offset;
    }
    if (intersection.first >= min(b.first.first,b.second.first) and
    intersection.first <= max(b.first.first,b.second.first) and
    intersection.first >= min(a.first.first,a.second.first) and
    intersection.first <= max(a.first.first,a.second.first) and
    intersection.second >= min(b.first.second,b.second.second) and
    intersection.second <= max(b.first.second,b.second.second) and
    intersection.second >= min(a.first.second,a.second.second) and
    intersection.second >= min(a.first.second,a.second.second) 
    ) {
            return make_pair(intersection,true);
    }
        else return make_pair(make_pair(0,0),false);
}

int main(){
    point a,b,c,d,e;
    a = {0,0};
    b = {2,2,};
    c = {0,2};
    d = {2,0};
    e = {1,1};
    segment ab, cd, ac, bd;
    ab = {a,b};
    cd = {c,d};
    ac = {a,c};
    bd = {b,d};

    point rv = single_intersection(ab,cd).first;
    assert(single_intersection(ab,cd).first == e);
    assert(single_intersection(ac,bd).second == false);

}