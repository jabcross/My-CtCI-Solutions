#include <bits/stdc++.h>

using namespace std;

// Since we can only access adjacent items at a single time, bubble-sort seems
// like a good fit. Pop two values, push in auxiliary stack in correct order,
// setting a flag if switched places. Do this until main stack is empty. Unwind
// the auxiliary stack. If the flag has been set, reset it and repeat.

void sort_stack(stack<int>& s) {
    bool       has_swapped = false;
    stack<int> tmp;
    while (true) {
        int  x, y;

        bool end_of_loop = false;
        if (s.empty()) {
            end_of_loop = true;
        } else {
            x = s.top();
            s.pop();
            if (s.empty()) {
                end_of_loop = true;
                tmp.push(x);
            } else {
                y = s.top();
                s.pop();
            }
        }

        if (end_of_loop) {
            while (!tmp.empty()) {
                s.push(tmp.top());
                tmp.pop();
            }
            if (has_swapped == false) {
                break;
            } else {
                has_swapped = false;
                continue;
            }
        }

        if (x <= y) {
            tmp.push(x);
            s.push(y);
        } else {
            tmp.push(y);
            s.push(x);
            has_swapped = true;
        }
    }
}

int main() {
    stack<int> my_stack;
    for (auto i : {1, 6, 2, 5, 3, 4}) { my_stack.push(i); }
    sort_stack(my_stack);
    for (auto i : {1, 2, 3, 4, 5, 6}) {
        assert(my_stack.top() == i);
        my_stack.pop();
    }

    cout << "Test passed" << endl;

    return 0;
}