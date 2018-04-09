#include <bits/stdc++.h>
using namespace std;

int queens(int           col,
           vector<bool>& rows,
           vector<bool>& dd,
           vector<bool>& ud,
           vector<int>&  output) {
    if (col == 8) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cout << ((output[i] == j) ? 'X' : '.');
            }
            cout << endl;
        }
        cout << endl;
        return 1;
    }
    int rv = 0;
    for (int i = 0; i < 8; i++) {
        if ((rows[i] == false) and (ud[i + col] == false) and
            (dd[i - col + 7] == 0)) {
            rows[i] = dd[i - col + 7] = ud[i + col] = true;
            output.push_back(i);
            rv += queens(col + 1, rows, dd, ud, output);
            output.pop_back();
            rows[i] = dd[i - col + 7] = ud[i + col] = false;
        }
    }
    return rv;
}

int main() {
    vector<bool> rows(8), dd(15), ud(15);
    vector<int>  output;
    int          answer = queens(0, rows, dd, ud, output);
    assert(answer == 92);
    return 0;
}