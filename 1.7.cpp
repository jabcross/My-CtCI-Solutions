#include <bits/stdc++.h>

using namespace std;

// In-place implementation.

class Pixel {
    public:
    vector<char> values;
    bool operator!=(Pixel b){
        for (int i = 0; i < 4; i++){
            if (values[i] != b.values[i]) return true;
        }
        return false;
    };
};

// For testing.
bool compare_matrixes(vector<vector<Pixel> > &a, vector<vector<Pixel> > &b){
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); i++){
        if (a[i].size() != b[i].size()) {
            return false;
        }
        for (int j = 0; j < a[i].size(); j++){
            if (a[i][j] != b[i][j]){
                return false;
            }
        }
    }
    return true;
}

// Rotates values counter-clockwise.
// Runtime: O(n*n) = BCR
void rotate(vector<vector<Pixel>> &matrix){
    assert(matrix.size() > 0);
    // Todo: assert that this is a square matrix
    for (int i = 0; i < (matrix.size()+2)/2 - 1; i++){
        int l = i, r = matrix.size()-i-1;
        for (int j = l; j < r; j++){
            Pixel tmp = matrix[l][j];
            matrix[l][j] = matrix[j][r];
            matrix[j][r] = matrix[r][r-j+l];
            matrix[r][r-j+l] = matrix[r-j+l][l];
            matrix[r-j+l][l] = tmp;
        }
    }
}   

int main(){
    Pixel red, green;
    vector<char> red_vals = {1,0,0,1};
    vector<char> green_vals = {0,1,0,1};

    red.values = red_vals;
    green.values = green_vals;
    vector<vector<Pixel> > mat1, mat2, mat3;
    mat1.push_back({green, green});
    mat1.push_back({green, red});
    
    mat2.push_back({green, red});
    mat2.push_back({green, green});
    
    mat3.push_back({red, green});
    mat3.push_back({green, green});


    rotate(mat1);
    assert(compare_matrixes(mat1, mat2));

    rotate(mat1);
    assert(compare_matrixes(mat1, mat3));

    cout << "Test passed" << endl;
    return 0;
}