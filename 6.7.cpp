#include <bits/stdc++.h>
using namespace std;
double simulate(int families){
    int boys = 0;
    int girls = 0;
    long int treshold = RAND_MAX/2;
    time_t seed;
    time(&seed);
    srandom(seed);
    for (int i = 0; i < families; i++){
        while (true){
            long int r = random();
            if (r > treshold){
                boys ++;
                continue;            
            }
            else {
                girls ++;
                break;
            }
        }
    }

    return (double) girls / (double) (girls + boys);
}

int main(){
    cout << "Female percentage:" << endl;
    for (int i : {1,10,100,1000,10000}){
        cout << i << " families: " << simulate(i) << endl;
    }
}