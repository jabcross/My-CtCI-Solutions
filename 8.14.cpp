#include <bits/stdc++.h>
#include <execinfo.h>
using namespace std;

map<tuple<int, int, bool>, int> memo;

int recurse(vector<bool>& values, vector<char>& ops, int l, int r, int value) {
    // cout << backtrace(NULL,100) << endl;
    auto memoize = memo.find(make_tuple(l, r, value));
    int  rv;
    if (memoize != memo.end())
        rv = memoize->second;
    else if (r - l == 1)
        rv = (values[l] == value);
    else {
        int acc = 0;
        for (int m = l + 1; m <= r - 1; m++) {
            int  left_true   = recurse(values, ops, l, m, true);
            int  left_false  = recurse(values, ops, l, m, false);
            int  right_true  = recurse(values, ops, m, r, true);
            int  right_false = recurse(values, ops, m, r, false);
            char op          = ops[m - 1];
            if (value) {
                if (op == '&') {
                    acc += left_true * right_true;
                } else if (op == '|') {
                    acc += left_true * right_false + right_true * left_false +
                           left_true * right_true;
                } else if (op = '^') {
                    acc += left_true * right_false + right_true * left_false;
                }
            } else {
                if (op == '&') {
                    acc += left_true * right_false + right_true * left_false +
                           left_false * right_false;

                } else if (op == '|') {
                    acc += left_false * right_false;

                } else if (op = '^') {
                    acc += left_true * right_true + right_false * left_false;
                }
            }
        }
        rv = acc;
    }
    memo[make_tuple(l, r, value)] = rv;
    return rv;
}

int bool_eval(string s, bool val){
    assert(s.size() % 2);
    memo.clear();
    vector<bool> values;
    vector<char> ops;
    for (int i = 0; i < s.size(); i++) {
        if (i % 2)
            ops.push_back(s[i]);
        else
            values.push_back(s[i] - '0');
    }
    return recurse(values, ops, 0, values.size(), val);
}

int main() {
    string s1 = "1^0|0|1";
    bool b1 = false;
    assert(bool_eval(s1,b1)==2);

    string s2 = "0&0&0&1^1|0";
    bool b2 = true;
    assert(bool_eval(s2,b2)==10);

}