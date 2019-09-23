// Sorted Search, No Size

#include <bits/stdc++.h>
using namespace std;

struct Listy {
   private:
    vector<unsigned int> vec;

   public:
    Listy(vector<unsigned int> _vec) {
        vec = _vec;
    }
    int elementAt(size_t i) {
        if (i >= vec.size())
            return -1;
        else
            return vec[i];
    }
};

int lowerBound(Listy &l, unsigned int value){
    if (l.elementAt(0) == -1) return -1;
    int ind = 1;
    unsigned int elem;
    while (true){
        elem = l.elementAt(ind-1);
        if (elem == -1) {
            int i = ind/2;
            while (true){
                elem = l.elementAt(i);
                if (elem == value) return i;
                if (elem == -1 or elem > value){
                    ind = i;
                    break;
                }
                i++;
            }
            break;
        }
        if (elem > value) break;
        if (elem == value) return ind-1;
        ind *= 2;
    }
    int p = 0, q = ind;
    while (p < q){
        if (p == q) return -1;
        if (p + 1 == q){
            if (l.elementAt(p) == value) return p;
            return -1;
        }
        int m = (p + q)/2;
        unsigned int elem = l.elementAt(m);        
        if (elem == value) return m;
        if (elem > value) q = m;
        else p = m;
    }
}

int main() {
    vector<unsigned int> test = {1,2,3,4,5,6,7,8,9,10};
    Listy y = Listy(test);
    assert(lowerBound(y,1) == 0);
    assert(lowerBound(y,2) == 1);
    assert(lowerBound(y,3) == 2);
    assert(lowerBound(y,4) == 3);
    assert(lowerBound(y,5) == 4);
    assert(lowerBound(y,6) == 5);
    assert(lowerBound(y,7) == 6);
    assert(lowerBound(y,8) == 7);
    assert(lowerBound(y,9) == 8);
    assert(lowerBound(y,10) == 9);
    assert(lowerBound(y,11) == -1);

    return 0;
}