#include <bits/stdc++.h>

using namespace std;

template<typename T>
class MyQueue {
    private:
        stack<T> inbox;
        stack<T> outbox;
    public:
        void push(T item) {
            while (!outbox.empty()){
                inbox.push(outbox.top());
                outbox.pop();
            }
            inbox.push(item);
        }

        bool pop(T* item){
            while (!inbox.empty()){
                outbox.push(inbox.top());
                inbox.pop();
            }
            if (outbox.empty()) return false;
            *item = outbox.top();
            outbox.pop();
            return true;
        }
};

int main(){

    MyQueue<int> q;
    for (auto i : {1,2,3,4,5,6,7}){
        q.push(i);
    }

    for (auto i : {1,2,3,4,5,6,7}){
        int rv;
        q.pop(&rv);
        assert(rv == i);
    }

    cout << "Test passed" << endl;

    return 0;
}