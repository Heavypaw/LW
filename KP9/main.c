#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINE_LENGTH 16

void swap(char* a, char* b) {
    if (a != b) {
        char t[100];
        strcpy(t, a);
        strcpy(a, b);
        strcpy(b, t);
    }
}

int partition (char arr[][5], char values[][100], int low, int high) {
    char pivot[5];
    strcpy(pivot, arr[high]);
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (atoi(arr[j]) < atoi(pivot)) {
            i++;
            swap(arr[i], arr[j]);
            swap(values[i], values[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    swap(values[i + 1], values[high]);
    return (i + 1);
}

void quickSort(char arr[][5], char values[][100], int low, int high) {
    if (low < high) {
        int pi = partition(arr, values, low, high);

        quickSort(arr, values, low, pi - 1);
        quickSort(arr, values, pi + 1, high);
    }
}

int binarySearch(char arr[][5], int l, int r, char* x) {
    int xInt = atoi(x);

    while (l <= r) {
        int mid = l + (r - l) / 2;
        int midInt = atoi(arr[mid]);

        if (midInt == xInt)
            return mid;

        if (midInt < xInt)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return -1;
}

int countLinesInFile(char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("error opening %s\n", filename);
        return -1;
    }

    int count = 0;
    char c;
    for (c = getc(file); c != EOF; c = getc(file)) {
        if (c == '\n') {
            count = count + 1;
        }
    }

    fclose(file);
    return count;
}

void readAsciiArtFromFile(char* filename, char** asciiArt, int size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("error opening %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        if (fgets(asciiArt[i], LINE_LENGTH, file) == NULL) {
            break;
        }

        asciiArt[i][strcspn(asciiArt[i], "\n")] = 0;
    }

    fclose(file);
}

void printTable(char keys[][5], char values[][100], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s, value: %s\n", keys[i], values[i]);
    }
}

/*

1. swap: O(n), где n - длина строки. Это потому, что функция strcpy имеет сложность O(n).
2. partition: O(n), где n - размер подмассива, который мы разделяем. Это потому, что мы проходимся по каждому элементу подмассива один раз.
3. quickSort: O(n log n) в среднем случае и O(n^2) в худшем случае, где n - размер массива. Это классическая сложность быстрой сортировки.
4. binarySearch: O(log n), где n - размер массива. Это классическая сложность бинарного поиска.
5. countLinesInFile: O(n), где n - количество символов в файле. Мы проходимся по каждому символу в файле один раз.
6. readAsciiArtFromFile: O(n), где n - количество строк в файле. Мы читаем каждую строку из файла один раз.
7. printTable: O(n), где n - количество строк в таблице. Мы печатаем каждую строку один раз.

*/

int main() {
    srand(time(0));
    char filename[100];
    printf("file: ");
    scanf("%s", filename);

    int size = countLinesInFile(filename);
    if (size == -1) {
        return 1;
    }

    char** asciiArt = malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        asciiArt[i] = malloc(LINE_LENGTH * sizeof(char));
    }

    readAsciiArtFromFile(filename, asciiArt, size);

    char keys[size][5];
    char values[size][100];

    int choice;
    printf("1. order\n2. reverse\n3. random\n");
    scanf("%d", &choice);

        switch(choice) {
        case 1:
            for (int i = 0; i < size; i++) {
                sprintf(keys[i], "%d", i);
                strncpy(values[i], asciiArt[i % size], 100);
            }
            break;
        case 2:
            for (int i = 0; i < size; i++) {
                sprintf(keys[i], "%d", size - i);
                strncpy(values[i], asciiArt[i % size], 100);
            }
            break;
        case 3:
            for (int i = 0; i < size; ) {
                int unique = 1;
                char tempKey[5];
                sprintf(tempKey, "%d", rand() % 91 + 10);

                for (int j = 0; j < i; j++) {
                    if (strcmp(keys[j], tempKey) == 0) {
                        unique = 0;
                        break;
                    }
                }

                if (unique) {
                    strcpy(keys[i], tempKey);
                    strncpy(values[i], asciiArt[i % size], 100);
                    i++;
                }
            }
            break;
        default:
            printf("bad choice\n");
            return 0;
    }

    printf("before:\n");
    printTable(keys, values, size);

    quickSort(keys, values, 0, size-1);

    printf("after:\n");
    printTable(keys, values, size);

    char* searchKey = malloc(8 * sizeof(char));
    printf("search by key: ");
    scanf("%s", searchKey);
    int result = binarySearch(keys, 0, size - 1, searchKey);

    if (result != -1) {
        printf("found, index: %d\n", result);
        printf("value: %s\n", values[result]);
    } else {
        printf("not found\n");
    }

    for (int i = 0; i < size; i++) {
        free(asciiArt[i]);
    }
    free(asciiArt);

    free(searchKey);
    return 0;
}
