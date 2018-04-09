#include <bits/stdc++.h>
using namespace std;

int main(){
    int a,b,c;
    vector<tuple<int,int,int,int>> input = {make_tuple(0,0,0,0)};
    while (cin >> a >> b >> c){
        input.push_back(make_tuple(a*b*c,a,b,c));
    }    
    vector<vector<int>> dp (input.size(),vector<int> (input.size(),0));

    for (int r = 1; r < input.size(); r++){
        for (int c = 1; c < input.size(); c++){
            int w_this, h_this, d_this;
            tie(ignore, w_this, h_this, d_this) = input[r];
            int stack = 0;
            int w_prev, h_prev, d_prev;
            tie(ignore, w_prev, h_prev, d_prev) = input[r-1];
            if (w_this > w_prev and h_this > h_prev and d_this > d_prev){
                stack = dp[r-1][c-1] + h_this;
            }
            else {
                stack = h_this;
            }
            int no_stack = dp[r-1][c];
            dp[r][c] = max(stack, no_stack);
        }
    }
    for (auto i: dp) {
        for (auto j: i){
            cout << j << ' ';
        }
        cout << "\n";
    }

    int max_height = 0;
    for (int i: dp.back()) max_height = max(max_height, i);
    cout << max_height << endl;
}