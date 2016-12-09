#include "naive.h"
#include "helpers.h"

void naive_diameter_2d(double *points, int size, int *answer) {
    for (int i = 0; i < size; i++) {
        int j = i + 1;
        for (; j < size && l2norm(&points[2 * i], &points[2 * j], 2) < 1.0;
               j++) {}
        answer[i] = j - 1;
    }
}