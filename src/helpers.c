#include <math.h>
#include "helpers.h"

double l2norm(double a[], double b[], int size) {
    double norm = 0.0;
    for (int i = 0; i < size; i++) {
        norm += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sqrt(norm);
}
