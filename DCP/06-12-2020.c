#include <stdlib.h>
#include <stdio.h>

/* problem:
 * An XOR linked list is a more memory efficient doubly linked list. 
 * Instead of each node holding next and prev fields, it holds a field 
 * named both, which is an XOR of the next node and the previous node. 
 *
 * Implement an XOR linked list; it has an add(element) which adds 
 * the element to the end, and a get(index) which returns the node at index.
 */

struct node {
    struct node* both;
    int data;
};

void LL_tostring(struct node* head) {
    if (head == NULL) return;
    printf("[%d]", head->data);
    struct node* prev = head;
    struct node* curr = head->both;
    struct node* next;
    unsigned long XOR;
    while (curr != NULL) {
        printf("->[%d]", curr->data);
        XOR = (unsigned long)(curr->both) ^ (unsigned long)(prev);
        next = (struct node*)(XOR);
        prev = curr;
        curr = next;
    }
    printf("\n");
}

void free_LL(struct node* head) {
    if (head == NULL) return;
    struct node* prev = head;
    struct node* curr = head->both;
    struct node* next;
    unsigned long XOR;
    while (curr != NULL) {
        XOR = (unsigned long)(curr->both) ^ (unsigned long)(prev);
        next = (struct node*)(XOR);
        prev = curr;
        free(curr);
        curr = next;
    }
}

struct node* add(struct node* head, int data) {
    struct node* new = malloc(sizeof(struct node));
    new->data = data;
    // linked list is empty
    if (head == NULL) {
        new->both = NULL;
        return new;
    // singleton linked list
    } else if (head->both == NULL) {
        head->both = new;
        new->both = head;
        return head;
    } else {
        struct node* prev = head;
        struct node* curr = head->both;
        struct node* next;
        unsigned long XOR;
        while (curr->both != prev) {
            XOR = (unsigned long)(curr->both) ^ (unsigned long)(prev);
            next = (struct node*)(XOR);
            prev = curr;
            curr = next;
        }
        XOR = (unsigned long)(prev) ^ (unsigned long)(new);
        curr->both = (struct node*) XOR;
        new->both = curr;
        return head;
    }
}

struct node* get(struct node* head, int index) {
    struct node* prev = 0;
    struct node* curr = head;
    struct node* next;
    unsigned long XOR;
    while (index > 0) {
        if (curr == NULL) break;
        XOR = (unsigned long)(curr->both) ^ (unsigned long)(prev);
        next = (struct node*) XOR;
        prev = curr;
        curr = next;
        index--;
    }
    if (curr == NULL) printf("linked list index out of bound\n");
    return curr;
}


int main() {
    
    struct node* LL1 = add(NULL,1);
    LL1 = add(LL1, 2);
    LL1 = add(LL1, 3);

    LL_tostring(LL1);

    struct node* res;
    for (int i = 0; i < 5; i++) {
        res = get(LL1, i);
        if (res != NULL) {
            printf("index %d: %d \n", i, res->data);
        }
    }

    free_LL(LL1);
    
    return 0;
}

