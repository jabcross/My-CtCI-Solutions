#include<bits/stdc++.h>
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

void delete_middle_node(Node* node){
    assert(node->next != NULL);
    node->value = node->next->value;
    Node* tmp = node->next;
    node->next = tmp->next;
    free(tmp);
}

int main(){
    Node* my_list = NULL;
    push_front(&my_list, 5);
    push_front(&my_list, 4);
    push_front(&my_list, 3);
    Node* to_be_deleted = my_list;
    push_front(&my_list, 2);
    push_front(&my_list, 1);

    delete_middle_node(to_be_deleted);

    Node* test_list = NULL;
    push_front(&test_list, 5);
    push_front(&test_list, 4);
    push_front(&test_list, 2);
    push_front(&test_list, 1);

    assert(cmp_lists(my_list, test_list));

    cout << "Tests passed" << endl;

    return 0;
}
