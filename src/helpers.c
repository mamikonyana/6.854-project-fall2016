#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"


double l2norm(double a[], double b[], int size) {
    double norm = 0.0;
    for (int i = 0; i < size; i++) {
        norm += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sqrt(norm);
}


int loadData(char *path, double *values) {
    const char DELIMITER[2] = ",";

    FILE *stream = fopen(path, "r");
    char line[1024];
    char *token;

    int num_columns = 0;

    // Consume header and calculate number of columns
    fgets(line, 1024, stream);
    token = strtok(line, DELIMITER);
    if (token == NULL) {
        num_columns = 1;
    }
    // Walk through other tokens
    while (token != NULL) {
        token = strtok(NULL, DELIMITER);
        num_columns += 1;
    }


    printf("there are %d columns\n", num_columns);
    int index = 0;

    while (fgets(line, 1024, stream)) {
        token = strtok(line, DELIMITER);
        values[index] = strtod(token, NULL);
        index += 1;
        for (int i = 1; i < num_columns; i++) {
            token = strtok(NULL, DELIMITER);
            values[index] = strtod(token, NULL);
            index += 1;
        }
    }
    return index;
}

/**
 * @param angle
 * @return a value in [0, 2PI)
 */
double standard_angle(double angle) {
    double multiple = angle / (2 * PI);
    double fraction = multiple - ((long) multiple);
    if (fraction < 0) {
        fraction = 1 + fraction;
    }
    return 2 * PI * fraction;
}

/**
 * @param vector: 4 array, x_0, y_0, x_e, y_e
 */
double angle(double *vector) {
    double dx = vector[2] - vector[0];
    double dy = vector[3] - vector[1];
    if (dx == 0) {
        if (dy > 0) {
            return PI / 2;
        } else if (dy < 0) {
            return -PI / 2;
        } else {
            return 0.0; // TODO: return something more informative. 10? :)
        }
    }
    double a = atan(dy / dx);
    if (dx > 0) {
        return standard_angle(a);
    } else {
        return standard_angle(a + PI);
    }
}


double max(double a, double b) {
    if (a > b) {
        return a;
    }
    return b;
}

double min(double a, double b) {
    if (a < b) {
        return a;
    }
    return b;
}

void positive_directions(double *vector, double *overlap, double *directions) {
    double direction = angle(vector);
    double range_begin = standard_angle(direction - PI / 2);
    double range_end = standard_angle(direction + PI / 2);
    if (overlap == NULL) {
        directions[0] = range_begin;
        directions[1] = range_end;
        return;
    }
    if (range_begin > range_end) {
        range_end += 2 * PI;
    }
    double before_begin = overlap[0];
    double before_end = overlap[1];
    if (before_begin > before_end) {
        before_end += 2 * PI;
    }
    double new_start = max(range_begin, before_begin);
    double new_end = min(range_end, before_end);
    if (new_start > new_end) {
        directions[0] = -1; // TODO: Better approach for reporting infeasible.
        return;
    }
    directions[0] = standard_angle(new_start);
    directions[1] = standard_angle(new_end);
}

