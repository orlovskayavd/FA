/*При реализации функции данного задания запрещается пользоваться строковым представлением числа в двоичной системе
счисления.Параметры, фигурирующие в условии, необходимо считать с клавиатуры.

1. Написать функцию поиска всех 𝑘− битных целых чисел, в двоичной записи которых присутствует ровно 𝑙, 𝑙≤𝑘 единиц.

2. Написать функцию поиска всех 𝑘− битных целых чисел, в двоичной записи которых присутствует ровно 𝑙, 𝑙≤𝑘 подряд идущих единиц.*/

#pragma warning(disable:4996)

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int countOf1InBinary(int num) {
    int count = 0;
    while (num != 0) {
        if (num % 2 != 0) count++;
        num /= 2;
    }
    return count;
}

bool seriesOfLExist(int num, int l) {
    int count = 0;

    while (num != 0) {
        if (num % 2 != 0) count++;
        else {

            count = 0;
        }
        if (count == l && ((num / 2) % 2 == 0 || num == 0)) return 1;
        num /= 2;
    }
    return 0;
}

int* first(int k, int l) {
    int max = 1 << k;
    int* result = (int*)malloc(sizeof(int) * BUFSIZ), * ptr = result;
    for (int i = 1 << (k - 1); i < max; ++i) {
        if (countOf1InBinary(i) == l) {
            *ptr++ = i;
        }
    }
    *ptr = 0;//Разыменование пустого указателя "ptr"
    return result;
}

int* second(int k, int l) {
    int max = 1 << k;
    int* result = (int*)malloc(sizeof(int) * BUFSIZ), * ptr = result;
    for (int i = 1 << (k - 1); i < max; ++i) {
        if (seriesOfLExist(i, l)) {
            *ptr++ = i;//11100111 при l = 3 тоже обрабатывать
        }
    }
    *ptr = 0;//Разыменование пустого указателя "ptr"
    return result;
} 


int main() {
    //    bool t = seriesOfLExist(119,3);
    int k, l;
    scanf("%d", &k);
    scanf("%d", &l);

    printf("FIRST:\n");
    int* result1 = first(k, l);

    int* r1 = result1;
    while (*r1 != 0)
        printf("%d\n", *r1++);

    printf("\n");
    printf("\n");
    printf("SECOND:\n");
    int* result2 = second(k, l);
    int* r2 = result2;

    while (*r2 != 0)
        printf("%d\n", *r2++);

    free(result1);
    free(result2);
}
