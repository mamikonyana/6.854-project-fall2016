#include<stdio.h>
#include <math.h>

double l2norm(double a[], double b[], int size) {
    double norm = 0.0;
    for (int i = 0; i < size; i++) {
        norm += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sqrt(norm);
}

void naive_diameter(double points[], int size, int answer[]) {
    for (int i = 0; i < size; i++) {
        int j = i + 1;
        for (; j < size && l2norm(&points[i], &points[j], 1) < 1.0;
               j++) {}
        answer[i] = j - 1;
    }
}

int main() {
    double p[5] = {0, 0.5, 1.1, 1.6, 2.0};
    int a[5];
    naive_diameter(p, 5, a);
    printf("Answers:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d\n", a[i]);
    }
}


