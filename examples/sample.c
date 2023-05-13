#include "../libraries/List.h"
#include <stdio.h>

int main() {
    struct list* root = genCollatzSequence(12345);
    printList(root);

    return 0;
}