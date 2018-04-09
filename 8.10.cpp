#include <bits/stdc++.h>
using namespace std;

void bucket_fill(
    vector<vector<int>>& grid, int r, int c, int color, int original) {
    if ((r < 0) or (r >= grid.size()) or (c < 0) or
        (c >= grid[0].size()) or (grid[r][c] == color)) {
        return;
    }
    if ((original != -1) and (grid[r][c] != original)) { return; }
    if (original == -1) {
        original   = grid[r][c];
    }
    grid[r][c] = color;

    bucket_fill(grid, r - 1, c, color, original);
    bucket_fill(grid, r, c - 1, color, original);
    bucket_fill(grid, r + 1, c, color, original);
    bucket_fill(grid, r, c + 1, color, original);
}

int main() {
    vector<vector<int>> grid = {
        {0,0,0,1,0},
        {0,0,0,1,0},
        {0,0,1,0,0},
        {0,1,0,0,0},
        {0,1,0,0,0},
    };

    bucket_fill(grid, 1,1,2,-1);

    for (auto i: grid){
        for (auto j: i) cout << j;
        cout<< endl;
    }

}