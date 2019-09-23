#include <bits/stdc++.h>

using namespace std;

// Moves chars based on how many spaces are found before its occurrence.
// Runtime: O(len(str))
void urlify(char* str){
    int length = strlen(str);
    int counter = 0;
    for (int i = 0; i < length; i++){
        if (str[i] == ' ') counter++;
    }
    str[length + 2 * counter] = '\0';
    for (int i = length - 1; counter > 0; i--){
        if (str[i] != ' '){
            str[i+2*counter] = str[i];
        }
        else {
            strncpy(str + i + 2*counter - 2, "%20", 3);
            counter --;
        }
    }
}

int main(){
    char str[256];
    strcpy(str,"Hello!");
    urlify(str);
    assert(strcmp(str,"Hello!") == 0);
    strcpy(str,"Hello, world!");
    urlify(str);
    assert(strcmp(str,"Hello,%20world!") == 0);
    strcpy(str,"The quick brown fox jumps over the lazy dog");
    urlify(str);
    assert(strcmp(str,"The%20quick%20brown%20fox%20jumps%20over%20the%20lazy%20dog") == 0);
    cout << "Tests passed." << endl;
    return 0;
}