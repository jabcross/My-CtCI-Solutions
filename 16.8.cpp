#include <bits/stdc++.h>
using namespace std;

const vector<string> tens = {"",
                             "",
                             "twenty",
                             "thirty",
                             "fourty",
                             "fifty",
                             "sixty",
                             "seventy",
                             "eighty",
                             "ninety"};

const vector<string> ones = {
    "zero",    "one",     "two",       "three",    "four",
    "five",    "six",     "seven",     "eight",    "nine",
    "ten",     "eleven",  "twelve",    "thirteen", "fourteen",
    "fifteen", "sixteen", "seventeen", "nineteen",
};


string to_english(int i) {
    assert(abs(i) <= 999999999);
    vector<string> rv;
    if (i < 0) {
        rv.push_back("negative");
        i *= -1;
    }
    if (i >= 1000000) {
        rv.push_back(to_english(i / 1000000) + " million");
        i %= 1000000;
    }
    if (i >= 1000) {
        rv.push_back(to_english(i / 1000) + " thousand");
        i %= 1000;
    }
    if (i >= 100) {
        rv.push_back(to_english(i / 100) + " hundred");
        i %= 100;
    }
    if (i >= 20) {
        rv.push_back(tens[i / 10]);
        rv.push_back(to_english(i % 10));
    } else {
        if (i != 0 or rv.size() == 0)
            rv.push_back(ones[i]);
    }
    string r = "";
    for (auto i : rv) r += i + " ";
    r.pop_back();
    return r;
}

int main() {
    cout << (to_english(-1005110)) << endl;
}