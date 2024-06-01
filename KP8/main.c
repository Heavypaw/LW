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

    // Use printList to display the nodes
    printf("nodes: ");
    printList(head);

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

    // Properly free the circular list
    if (head != NULL) {
        Node* temp = head;
        do {
            Node* next = temp->next;
            free(temp);
            temp = next;
        } while (temp != head);
    }

    return 0;
}
