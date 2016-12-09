#include <stdio.h>
#include "bce.h"
#include "naive.h"

int main() {
    const int size = 5;
    double p[size] = {0, 0.5, 1.1, 1.6, 2.0};
    int a[size];
    naive_diameter(p, size, a);
    printf("Answers:\n");
    for (int i = 0; i < size; i++) {
        printf("%d\n", a[i]);
    }
    printf("BCE Answers:\n");
    int bce_a[size];
    bce_diameter(p, size, bce_a);
    for (int i = 0; i < size; i++) {
        printf("%d\n", bce_a[i]);
    }

}


