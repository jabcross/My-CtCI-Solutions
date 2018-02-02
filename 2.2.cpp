#include <bits/stdc++.h>
using namespace std;

typedef struct Node {
    int value;
    Node* next;
} Node;

void push_front(Node** root, int value){
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = *root;
    *root = new_node;
}

Node* kth_to_last(Node *root, int k){
    if (k <= 0){
        return NULL;
    }
    int counter = k-1;
    Node* base = root;
    Node* scout = root;

    while(counter--){
        if (scout->next == NULL){
            return NULL;
        }
        scout = scout->next;
    }

    while(scout->next != NULL){
        scout = scout->next;
        base = base->next;
    }

    return base;
}

int main(){
    Node* my_list = NULL;

    push_front(&my_list,4);
    push_front(&my_list,3);
    push_front(&my_list,2);
    push_front(&my_list,1);

    Node* rv = kth_to_last(my_list, 3);

    assert(rv != NULL);
    assert(rv->value == 2);

    rv = kth_to_last(my_list, 5);
    assert(rv == NULL);

    rv = kth_to_last(my_list, -2);
    assert(rv == NULL);

    cout << "Tests passed" << endl;

    return 0;
}