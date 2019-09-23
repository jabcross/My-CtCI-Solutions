#include <bits/stdc++.h>

using namespace std;

class Ranker{
    class Node {
        int val;
        int count;
        int sum;
        Node* l, *r;
    public:
        Node(int _val) {
            val = _val;
            count = 0;
            l = r = NULL;
        };

        void track(int i){
            sum++;
            if (val == i){
                count++;
            }
            if (val < i){
                if (r == NULL){
                    r = new Node(i);
                }
                r->track(i);
            }
            if (val > i){
                if (l == NULL){
                    l = new Node(i);
                }
                l->track(i);
            }
        };

        int getRankOfNumber(int i){
            if (i == val){
                int rv = count;
                if (l) rv += l->sum;
                return rv;
            }
            if (i < val){
                if (l) return l->getRankOfNumber(i);
                else return 0;
            }
            if (i > val){
                int rv = count;
                if (r) rv += r->getRankOfNumber(i);
                if (l) rv += l->sum;
                return rv;
            }
        }

        void print(){
            cout << " ( ";
            if (l) l->print();
            cout <<val << ":" << ":" << sum;
            if (r) r->print();
            cout << " ) ";
        }
    };

    Node *ranker;

    public:

    void track(int i){
        if (!ranker) ranker = new Node(i);
        return ranker->track(i);
    }

    int getRankOfNumber(int i){
        if (!ranker) return 0;
        else return ranker->getRankOfNumber(i) - 1;
    }

    void print(){
        if (ranker) ranker->print();
    }

};

int main(){
    Ranker ranker = Ranker();
    vector<int> input = {5,1,4,4,5,9,7,13,3};
    for (auto i: input) ranker.track(i);
    ranker.print();
    cout << ranker.getRankOfNumber(1) << endl;
    assert(ranker.getRankOfNumber(1) == 0);
    assert(ranker.getRankOfNumber(3) == 1);
    assert(ranker.getRankOfNumber(4) == 3);
}