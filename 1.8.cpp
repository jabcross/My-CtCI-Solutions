#include <bits/stdc++.h>

using namespace std;

// Sets rows and columns that contain 0s to 0 
void zero_matrix(vector<vector<int> > &matrix){
    // todo: assert valid matrix
    vector<bool> rows(matrix.size(), false);
    vector<bool> cols(matrix[0].size(), false);

    for (int r = 0; r < matrix.size(); r++){
        for (int c = 0; c < matrix[0].size(); c++){
            if (matrix[r][c] == 0){
                rows[r] = true;
                cols[c] = true;
            }
        }
    }

    for (int r = 0; r < matrix.size(); r++){
        for (int c = 0; c < matrix[0].size(); c++){
            if (rows[r] or cols[c]){
                matrix[r][c] = 0;
            }
        }
    }
}

int main(){
    vector<vector<int> > v;
    v.push_back({1,2,0});
    v.push_back({4,5,6});
    v.push_back({7,8,9});

    vector<vector<int> > u;
    u.push_back({0,0,0});
    u.push_back({4,5,0});
    u.push_back({7,8,0});

    zero_matrix(v);

    assert(u == v);
    
    cout << "Test Passed" << endl;
    return 0;
}