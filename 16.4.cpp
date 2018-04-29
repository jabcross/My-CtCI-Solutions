#include <bits/stdc++.h>

using namespace std;

// Since the input format is not specified, I'm not checking for invalid
// cases here. However, some ideas would be:
// 1- checking if the number of Xs is always either equal to the number
//    of Os or one more;
// 2- checking for invalid characters (other than 'x', 'o' and ' ')

char who_won(char (&board)[3][3]){
    // returns 'x' if X won, 'o' if O won, ' ' if no one won
    
    // check rows
    for (int r = 0; r < 3; r++){
        if (board[r][0] != ' ' and board[r][0] == board[r][1] and board[r][1] == board[r][2]){
            return board[r][0];
        }
    }
    // check cols
    for (int c = 0; c < 3; c++){
        if (board[0][c] != ' ' and board[0][c] == board[1][c] and board[1][c] == board[2][c]){
            return board[0][c];
        }
    }
    // check diagonals
    if (board[0][0] != ' ' and board[0][0] == board[1][1] and board[1][1] == board[2][2]){
        return board[0][0];
    }
    if (board[0][2] != ' ' and board[0][2] == board[1][1] and board[1][1] == board[2][0]){
        return board[0][2];
    }
    return ' ';
}

int main(){
    char a [3][3] = {
        {' ',' ',' '},
        {'x','x','x'},
        {'o','o',' '}
    };

    char b [3][3] = {
        {'o','x',' '},
        {'x','o',' '},
        {'x','x','o'}
    };

    char c [3][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };

    assert(who_won(a)=='x');
    assert(who_won(b)=='o');
    assert(who_won(c)==' ');
}