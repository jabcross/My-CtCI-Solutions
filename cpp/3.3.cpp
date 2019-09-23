#include <bits/stdc++.h>

using namespace std;

template <typename T, size_t max_height>
class SetOfStacks {
   private:
    vector<stack<T>> set_of_stacks;
    size_t           total = 0;

   public:
    SetOfStacks() {
        total = 0;
    }
    void push(T item) {
        if ((set_of_stacks.empty()) or
            (set_of_stacks.back().size() == max_height)) {
            set_of_stacks.push_back(stack<T>());
        }
        set_of_stacks.back().push(item);
        total++;
    }
    bool pop(T* target) {  // i miss optionals.
        if (total = 0) return false;
        *target = set_of_stacks.back().top();
        set_of_stacks.back().pop();
        if (set_of_stacks.back().empty()) { set_of_stacks.pop_back(); }
        total--;
        return true;
    }
    bool popAt(T* target, size_t sub_stack) {
        if (sub_stack >= set_of_stacks.size()) return false;
        *target = set_of_stacks[sub_stack].top();
        set_of_stacks[sub_stack].pop();
        if (set_of_stacks[sub_stack].empty()) {
            set_of_stacks.erase(set_of_stacks.begin() + sub_stack);
        }
    }
};

int main() {
    auto sos = SetOfStacks<int, 3>();
    sos.push(1);
    sos.push(2);
    int rv;
    sos.pop(&rv);
    assert(rv == 2);
    sos.pop(&rv);
    assert(rv == 1);

    sos.push(1);
    sos.push(2);
    sos.push(3);

    sos.push(4);
    sos.push(5);
    sos.push(6);
    
    sos.push(7);

    sos.popAt(&rv, 0);
    assert(rv == 3);
    sos.popAt(&rv, 1);
    assert(rv == 6);
    sos.popAt(&rv, 2);
    assert(rv == 7);

    cout << "Tests passed" << endl;

    return 0;
}