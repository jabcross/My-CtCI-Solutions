// Search in Rotated Array
#include <bits/stdc++.h>
using namespace std;

struct RotatedSortedArray {
   public:
    vector<int>* vec;
    RotatedSortedArray(vector<int>* _vec) {
        vec = _vec;
    }

    int search_rot(int value) {
        auto it = search_rot(vec->begin(), vec->end(), value);
        if (it == vec->end())
            return -1;
        else
            return distance(vec->begin(), it);
    }

   private:
    vector<int>::iterator search_rot(vector<int>::iterator l,
                                     vector<int>::iterator r,
                                     int                   value) {
        if (l == r) return r;
        if (l + 1 == r) {
            if (*l == value)
                return l;
            else
                return r;
        }
        auto m = l + distance(l, r) / 2;
        if (value == *m) return m;
        if (value == *l) l;
        if (value == *(r - 1)) return r - 1;
        if (*m < *(r - 1)) {
            if (value >= *m and value <= *(r - 1)) {
                auto it = lower_bound(m, r, value);
                if (it != r) return it;
            }
            auto rv = search_rot(l, m, value);
            if (rv == m) return r;
            return rv;
        } else if (*l < *m) {
            if (value >= *l and value <= *m) {
                auto it = lower_bound(l, m, value);
                if (it != m) return it;
            }
            auto rv = search_rot(m, r, value);
            return r;
        }
        auto rv = search_rot(l, m, value);
        if (rv == m) { rv = search_rot(m, r, value); }
        return rv;
    }
};


int main() {
    vector<int> a_v = {4, 5, 6, 7, 8, 9, 1, 2, 3};
    auto        a   = RotatedSortedArray(&a_v);
    vector<int> b_v = {8, 9, 1, 2, 3, 4, 5, 6, 7};
    auto        b   = RotatedSortedArray(&b_v);
    assert(a.search_rot(6) == 2);
    assert(b.search_rot(6) == 7);
    assert(a.search_rot(10) == -1);
    return 0;
}