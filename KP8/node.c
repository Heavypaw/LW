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
    if (head == NULL) {
        newNode->next = newNode; // Сам на себя, если это первый узел
    } else {
        Node* temp = head;
        while (temp->next != head) { // Найти последний узел
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }
    return newNode; // новый узел становится головой
}

Node* deleteNode(Node* head, size_t key) {
    if (head == NULL) return NULL;

    Node* temp = head, *prev = NULL;
    do {
        if (temp->data == key) {
            if (prev == NULL) { // Удаление головы списка
                if (temp->next == head) { // Единственный элемент
                    free(temp);
                    return NULL;
                } else {
                    Node* last = head;
                    while (last->next != head) last = last->next;
                    head = head->next;
                    last->next = head;
                    free(temp);
                    return head;
                }
            } else {
                prev->next = temp->next;
                free(temp);
                return head;
            }
        }
        prev = temp;
        temp = temp->next;
    } while (temp != head);

    return head; // Ключ не найден
}

int countNodes(Node* head) {
    if (head == NULL) return 0;

    int count = 1;
    Node* current = head->next;
    while (current != head) {
        count++;
        current = current->next;
    }
    return count;
}

void printList(Node* head) {
    if (head == NULL) return;

    Node* temp = head;
    do {
        printf("%zu ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
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
