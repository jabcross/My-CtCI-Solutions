#include <bits/stdc++.h>
using namespace std;


int main(){
    vector<int> sieve;
    for (int i = 1; i < 100; i++){
        sieve.push_back(i);
    }
    vector<int> primes;

    vector<bool> cross (100, false);

    cross[1] = true;

    int current = 1;

    while (current <= 99){
        // encontrar proximo primo
        while (cross[current]) current = current + 1;
        primes.push_back(current);
        for (int i = 2*current; i <= 99; i+=current){
            cross[i] = true;
        }
        current ++;
    }

    for (int i = 0; i < primes.size(); i+= 2) cout << primes[i] << endl;
    cout << endl;
    for (int i = 1; i < primes.size(); i+= 2) cout << primes[i] << endl;


    cout << endl;
}