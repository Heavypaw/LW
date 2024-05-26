#include "udt.h"
#include <stdlib.h>
#include <stdio.h>

udt* udt_create(int capacity) {
	udt* queue = (udt*)malloc(sizeof(udt));
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1;
	queue->data = (int*)malloc(queue->capacity * sizeof(int));
	return queue;
}

bool udt_is_empty(const udt *queue) {
	return (queue->size == 0);
}

void udt_push(udt *queue, int item) {
	if (queue->size == queue->capacity) return;
	queue->rear = (queue->rear + 1)%queue->capacity;
	queue->data[queue->rear] = item;
	queue->size = queue->size + 1;
}

void udt_pop(udt *queue) {
	if (udt_is_empty(queue)) return;
	queue->front = (queue->front + 1)%queue->capacity;
	queue->size = queue->size - 1;
}

int udt_get(const udt* queue) {
	return queue->data[queue->front];
}

void udt_print(const udt* queue) {
	int i;
	for (i = 0; i < queue->size; i++) {
		printf("%d ", queue->data[i]);
	}
	printf("\n");
}

int udt_size(const udt *queue) {
	return queue->size;
}

void udt_destroy(udt* queue) {
    free(queue->data);
    free(queue);
}

/*

Функция udt_insert_sorted имеет сложность O(n), где n - это размер очереди. Это связано с тем, что в худшем случае (когда вставляемый элемент меньше всех элементов в очереди) функция проходит через все элементы очереди.
Функция udt_insertion_sort имеет сложность O(n^2), где n - это размер очереди. Это связано с тем, что функция udt_insert_sorted вызывается для каждого элемента в очереди. Поскольку udt_insert_sorted имеет сложность O(n), общая сложность становится O(n^2).

*/

void udt_insert_sorted(udt *queue, int item) {
    if (queue->size == queue->capacity) return;
    int i;
    for (i = queue->size - 1; (i >= 0 && queue->data[i] > item); i--)
        queue->data[i + 1] = queue->data[i];
    queue->data[i + 1] = item;
    queue->size = queue->size + 1;
}

void udt_insertion_sort(udt *queue) {
    int i, item;
    udt* temp_queue = udt_create(queue->capacity);
    for (i = 0; i < queue->size; i++) {
        item = queue->data[i];
        udt_insert_sorted(temp_queue, item);
    }
    for (i = 0; i < temp_queue->size; i++) {
        queue->data[i] = temp_queue->data[i];
    }
    queue->size = temp_queue->size;
    udt_destroy(temp_queue);
}
