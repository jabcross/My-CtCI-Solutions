#include <bits/stdc++.h>

using namespace std;

typedef struct Node {
    int   value;
    Node* next;
} Node;

void push_front(Node** root, int value) {
    Node* new_node  = (Node*) malloc(sizeof(Node));
    new_node->value = value;
    new_node->next  = *root;
    *root           = new_node;
}

char cmp_lists(Node* root_a, Node* root_b) {
    while (1) {
        if ((root_a == NULL) != (root_b == NULL)) { return false; }
        if (root_a != NULL) {
            if (root_a->value != root_b->value) { return false; }
            root_a = root_a->next;
            root_b = root_b->next;
        } else
            return true;
    }
}

Node* find_loop(Node* root) {
    Node *base, *scout;
    base = scout = root;

    if (root == NULL) return NULL;
    if (root->next == NULL) return NULL;
    if (root->next->next == NULL) return NULL;

    base  = base->next;
    scout = base->next;

    while (base != scout){
        if (scout->next == NULL) return NULL;
        if (scout->next->next == NULL) return NULL;
        scout = scout->next->next;
        base = base->next;
    }

    scout = root;

    while (base != scout){
        base = base->next;
        scout = scout->next;
    }

    return base;
}

int main(){
    Node* l = NULL;

    for (auto i: {9,8,7,6,5,4,3,2,1}){
        push_front(&l,i);
    }

    Node *center, *end = l;

    while (end->next != NULL){
        if (end->value == 5) center = end;
        end = end->next;
    }

    end->next = center;

    assert(find_loop(l) == center);

    cout << "Test passed" << endl;

}