#include <stdio.h>
#include <stdlib.h>
#include "node.h"

Iterator* createIterator(Node* head) {
    Iterator* it = (Iterator*)malloc(sizeof(Iterator));
    it->current = head;
    return it;
}

Node* next(Iterator* it) {
    if (it->current == NULL) {
        return NULL;
    }
    Node* node = it->current;
    it->current = it->current->next;
    return node;
}

Node* createNode(size_t data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* insertNode(Node* head, size_t data) {
    Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

Node* deleteNode(Node* head, size_t key) {
    Node* temp = head, *prev = NULL;

    if (temp != NULL && temp->data == key) {
        head = temp->next;
        free(temp);
        return head;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return head;

    prev->next = temp->next;
    free(temp);

    return head;
}

int countNodes(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void printList(Node* head) {
    Iterator* it = createIterator(head);
    Node* current;

    while ((current = next(it)) != NULL) {
        printf("%zu ", current->data);
    }
    printf("\n");

    free(it);
}

Node* deleteMiddleXNodes(Node* head, int X) {
    int totalNodes = countNodes(head);
    int start = totalNodes / 2 - X / 2;
    int end = start + X;

    // If there are not enough nodes in the middle, delete from the ends
    if (start < 0) {
        start = 0;
        end = X;
    }
    if (end > totalNodes) {
        end = totalNodes;
    }

    Iterator* it = createIterator(head);
    Node* current;
    Node* prev = NULL;
    int count = 0;

    // Traverse to the start position
    while ((current = next(it)) != NULL && count < start) {
        prev = current;
        count++;
    }

    // Delete X nodes
    for (int i = start; i < end; i++) {
        if (current == NULL) {
            break;
        }
        Node* nextNode = current->next;
        free(current);
        current = nextNode;
    }

    // Link the previous node to the current node
    if (prev != NULL) {
        prev->next = current;
    } else {
        // If start was the head of the list
        head = current;
    }

    free(it);

    return head;
}

