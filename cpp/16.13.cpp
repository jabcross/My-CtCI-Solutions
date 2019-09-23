#include <bits/stdc++.h>
#include "geometry.h"

Line bisectTwoSquares(Rect a, Rect b){
    Point center1 = (a.topleft + a.bottomright)/2;
    Point center2 = (b.topleft + b.bottomright)/2;
    if (center1 == center2) return Line(center1,center1*2);
    return Line(center1,center2);
}

int main(){
    Rect p = Rect(Point(0,1),Point(1,0));
    Rect q = Rect(Point(3,4),Point(4,3));
    Line x = bisectTwoSquares(p,q);
    // 45 degree line
    assert(x.a == -1 and x.b == 1 and x.c == 0);
    p = Rect(Point(0,1),Point(1,0));
    q = Rect(Point(0,4),Point(1,3));
    x = bisectTwoSquares(p,q);
    // vertical line
    assert(x.a == 1 and x.b == 0 and x.c == -0.5);

}