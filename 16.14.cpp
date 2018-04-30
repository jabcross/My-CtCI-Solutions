#include <bits/stdc++.h>
#include "geometry.h"

Line find_most_popular_line(std::vector<Point> &v){
    struct node{int count; Line line;};
    std::unordered_map<Line, int> hashmap;
    std::pair<int,Line> maximum;
    for (int i = 0; i < v.size(); i++){
        for (int j = 0; j < i; j++){
            Line x = Line(v[i],v[j]);
            hashmap[x] ++;
            maximum = std::max(std::make_pair(hashmap[x],x),maximum); 
        }
    }
    return maximum.second;
}

int main(){
    std::vector<Point> v = {Point(0,0),Point(1,1),Point(2,2),Point(0,2)};
    Line expected = Line(Point(0,0),Point(1,1));
    Line rv = find_most_popular_line(v);
    assert(rv == expected);
}
