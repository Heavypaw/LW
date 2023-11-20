# Отчет по лабораторной работе № 7
## по курсу "Фундаментальная информатика"

Студент группы 108Б Болотин Антон Николаевич

Работа выполнена

Преподаватель: каф. 806 Севастьянов Виктор Сергеевич

1.Тема: Задачи на Cи

2.Цель работы: решить задачу с помощью языка Си 

З.3адание: вариант №26

4.Идея, метод, алгоритм решения задачи: 
Имитация шага, вовремя каждого из них происходит проверка нахождения в треугольнике

5.Сценарий выполнения работы:
Шаг, проверка на вхождение в треугольник, если да, то конец, если нет, то продолжать выполнение


```
#include <stdio.h>

int sign(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

int area(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2;
}

int isInsideTriangle(int x, int y) {
    int x1 = -10, y1 = 0;
    int x2 = 0, y2 = 10;
    int x3 = -10, y3 = -20;

    int A = area(x1, y1, x2, y2, x3, y3);
    int A1 = area(x, y, x2, y2, x3, y3);
    int A2 = area(x1, y1, x, y, x3, y3);
    int A3 = area(x1, y1, x2, y2, x, y);

    return sign(A) == sign(A1) && sign(A) == sign(A2) && sign(A) == sign(A3);
}

int main() {
    int i = 8, j = -22, l = 10;
    int max_steps = 50;

    int triangle_hit = 0;

    for (int step = 1; step <= max_steps; ++step) {
        int next_i = (i - j > j - i ? (i - j) % 20 : (j - i) % 20) + 10;
        int next_j = sign(i - j) * (i % 20 < j % 20 ? i % 20 : j % 20) - 
                     ((i - l > l - i ? i - l : l - i) % 20) + 20;
        int next_l = (i % 10) * (j % 10) + l % 10;

        printf("Step %d: i = %d, j = %d, l = %d\n", step, i, j, l);

        if (isInsideTriangle(i, j)) {
            printf("Попадание в треугольник!\n");
            triangle_hit = 1;
            break;
        }

        i = next_i;
        j = next_j;
        l = next_l;
    }

    printf("Конечные координаты: i = %d, j = %d, l = %d\n", i, j, l);

    if (!triangle_hit) {
        printf("Точка не попала в треугольник за 50 шагов.\n");
    }

    return 0;
}
```

6. Замечания автора по существу работы: 
Замечаний нет

7. Выводы:
Было достаточно сложно, ведь с этим языком я на Вы. Но через боль, кровь и страдания, я смог написать этот код, который вроде бы даже работает

 
