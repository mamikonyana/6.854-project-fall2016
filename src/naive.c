#include "naive.h"
#include "helpers.h"



void naive_diameter(double points[], int size, int answer[]) {
    for (int i = 0; i < size; i++) {
        int j = i + 1;
        for (; j < size && l2norm(&points[i], &points[j], 1) < 1.0;
               j++) {}
        answer[i] = j - 1;
    }
}