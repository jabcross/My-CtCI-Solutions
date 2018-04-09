#include <bits/stdc++.h>
using namespace std;

struct FrequencyInfo {
    unordered_map<string, int> hashmap;
    long long int total_words;
    FrequencyInfo () {
        string word;
        FrequencyInfo rv;
        while (cin >> word){
            // Ignoring punctuation, etc
            hashmap[word] ++;
            total_words ++;
        }
    }
    double get_frequency (string word){
        return (double)hashmap[word] / (double)total_words;
    }
};

