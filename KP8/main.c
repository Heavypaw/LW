#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main() {
    Node* head = NULL;
    int num, data;

    printf("Enter the number of elements in the list: ");
    scanf("%d", &num);

    printf("Enter the elements of the list: ");
    for (int i = 0; i < num; i++) {
        scanf("%d", &data);
        head = insertNode(head, data);
    }

    Iterator* it = createIterator(head);
    printf("nodes: ");
    Node* node;
    while ((node = next(it)) != NULL) {
        printf("%zu ", node->data);
    }
    printf("\n");

    int count = countNodes(head);
    printf("#nodes: %d\n", count);

    printf("Enter the number to delete: ");
    scanf("%d", &data);

    head = deleteNode(head, data);
    printf("delete node %d: ", data);
    printList(head);

    head = deleteMiddleXNodes(head, 3);
    printf("delete middle 3: ");
    printList(head);

    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    free(it);

    return 0;
}
