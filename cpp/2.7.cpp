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

char cmp_lists(Node* root_a, Node* root_b){
    while (1){
        if ((root_a == NULL) != (root_b == NULL)){
            return false;
        }
        if (root_a != NULL){
            if (root_a->value != root_b->value){
                return false;
            }
            root_a = root_a->next;
            root_b = root_b->next;
        }
        else return true;
    }
}


Node* find_intersection(Node* a,
                        Node* b) {
    if ((a == NULL) or (b == NULL)){
        return NULL;
    }

    Node* last_a;
    int count_a = 0;

    for (Node* i = a; i->next != NULL; i = i->next){
        last_a = i;
        count_a ++;
    }

    Node* last_b;
    int count_b = 0;

    for (Node* i = b; i->next != NULL; i = i->next){
        last_b = i;
        count_b ++;
    }

    if (last_a != last_b) return NULL;

    Node *biggest = a, *smallest = b;
    int count_big = count_a, count_small = count_b;

    if (count_a < count_b) {
        swap(biggest,smallest);
        swap(count_big,count_small);
    }

    while (count_big > count_small) {
        biggest = biggest->next;
        count_big --;
    }
    
    while (biggest != smallest) {
        biggest = biggest->next;
        smallest = smallest->next;
    }

    return biggest;
}

int main() {

    // 1-3-5-(6)-7-8-9
    //      /
    //   2-4

    Node* list_a = NULL;
    
    push_front(&list_a, 9);
    push_front(&list_a, 8);
    push_front(&list_a, 7);
    push_front(&list_a, 6);

    Node* list_b = NULL;
    push_front(&list_b, 4);
    list_b->next = list_a;
    push_front(&list_b, 2);

    push_front(&list_a, 5);
    push_front(&list_a, 3);
    push_front(&list_a, 1);
        
    Node* intersection = find_intersection(list_a, list_b);

    assert(intersection->value == 6);

    cout << "Test passed" << endl;

    return 0;
}