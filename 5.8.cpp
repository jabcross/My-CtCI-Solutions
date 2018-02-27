#include <bits/stdc++.h>
using namespace std;

void drawLine(unsigned char* screen, int width, int x1, int x2, int y) {
    int headstart = y * width / 8;
    for (int i = x1; i <= x2; i++) {
        screen[headstart + i / 8] |= (1 << (i % 8));
    }
}

void print(char x){
    for (int i = 0; i < 8; i++){
        cout << ((x>>(7-i)) & 1);
    }
    cout << endl;
}

int main() {
    unsigned char screen[] = {0b00000000,0b00000000,0b00000000,
                              0b00000000,0b00000000,0b00000000,
                              0b00000000,0b00000000,0b00000000};
    drawLine(screen, 24, 3, 20, 1);

    print (screen[3]);
    print (screen[4]);
    print (screen[5]);

    assert(screen[3] == 0b11111000);
    assert(screen[4] == 0b11111111);
    assert(screen[5] == 0b00011111);
    cout << "Test passed" << endl;
    return 0;
}
