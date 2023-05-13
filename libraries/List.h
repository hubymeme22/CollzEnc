/*
    Simple Linked List for storing collatz sequence output,
    since the collatz sequence will be used one-time, then it'll
    be reasonable to use a simple singly linkedlist.

    By: Hubert F. Espinola I (HueHueberry)
*/

#include <stdlib.h>
#include <stdio.h>

struct list {
    int data;
    struct list* next;
};

int LIMITING_SIZE = 1024;
int CURRENT_SIZE = 0;

// sets the limit for the list that will be generated
void setLimit(int n) {
    LIMITING_SIZE = n;
}

// connects two nodes
void connectNode(struct list* left, struct list* right) {
    left->next = right;
}

// for debugging (printing all values inside the list)
void printList(struct list* root) {
    if (!root) return;

    while (root->next) {
        if (!root->next->next) {
            printf(" %d", root->data);
            break;
        }

        printf(" %d |", root->data);
        root = root->next;
    }

    puts("");
}

// generates a new node with the provided integer n as data value
struct list* genNode(int n) {
    struct list* node = malloc(sizeof(struct list));
    node->data = n;
    node->next = NULL;

    return node;
}

// generates a collatz sequence of numbers with the given
// number n, which will be used for 3n + 1 and n/2
struct list* genCollatzSequence(int n) {
    struct list* root = genNode(n);
    struct list* curr = root;

    while ((CURRENT_SIZE < LIMITING_SIZE) && (n > 1)) {
        if (n % 2 == 0)
            n = (n / 2);
        else
            n = (3 * n) + 1;

        struct list* newNode = genNode(n);
        connectNode(curr, newNode);
        curr = newNode;
    }

    return root;
}