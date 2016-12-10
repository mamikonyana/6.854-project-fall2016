#include <printf.h>
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

void naive_monotonicity_2d(double *points, int size, int *answer) {
    for (int i = 0; i < size; i++) {
        int j = i;
        for (; j < size - 1; j++) {
            double range[2];
            if (j == i) {
                positive_directions(&points[2 * j], NULL, range);
            } else {
                positive_directions(&points[2 * j], range, range);
            }
            // printf(" ================ i: %d, j: %d, angles: %.1f, %1f \n", i, j, range[0] * 180 / PI, range[1] * 180 / PI);
            if (range[0] < 0) {
                break;
            }
        }
        answer[i] = j;
    }
}