#include <stdio.h>
#include "bce.h"
#include "naive.h"

int main() {
    const int size = 5;
    double p[2 * size] = {0, 0,
                          0.5, 0,
                          1.1, 0,
                          1.6, 0,
                          2.0, 0};
    int a[size];
    naive_diameter_2d(p, size, a);
    printf("Answers:\n");
    for (int i = 0; i < size; i++) {
        printf("%d\n", a[i]);
    }
    printf("BCE Answers:\n");
    int bce_a[size];
    bce_diameter_2d(p, size, bce_a);
    for (int i = 0; i < size; i++) {
        printf("%d\n", bce_a[i]);
    }

}


