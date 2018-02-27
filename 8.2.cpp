#include <bits/stdc++.h>
using namespace std;

// Returns path from top-left to bottom-right, in reverse order
vector<char>* find_path(vector<vector<bool> > &obstacles){
    vector<char>* rv = new vector<char>;
    int rows = obstacles.size();
    int cols = obstacles[0].size();

    vector<vector<char> > my_map (rows,vector<char>(cols, 0));

    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            if ((r == 0) and (c == 0)){
                my_map[r][c] = 's';
                continue;
            }
            my_map[r][c] = 'n';
            if (obstacles[r][c]){
                continue;
            }
            if ((c > 0) and (my_map[r][c-1]!= 'n')){
                my_map[r][c] = 'r';
                continue;
            }
            if ((r > 0) and (my_map[r-1][c]!= 'n')){
                my_map[r][c] = 'd';
                continue;
            }
        }
    }
    rows--, cols--;
    if (my_map[rows][cols] == 'n'){
        return rv;
    }
    while ((rows > 0) or (cols > 0)){
        rv->push_back(my_map[rows][cols]);
        switch(my_map[rows][cols]){
            case 'd':
            rows--;
            break;
            case 'r':
            cols--;
            break;
        }
    }
    return rv;
} 

int main(){
    
    vector<vector<bool> > my_map = {
{0,1,0,0,0},
{0,0,0,1,0},
{0,1,0,0,0}
    };

    auto path = find_path(my_map);

    vector<char> test = {'r','r','d','r','r','d'};

    for (int i = 0; i < test.size(); i++) assert((*path)[i] == test[i]);

    free(path);
    return 0;
}