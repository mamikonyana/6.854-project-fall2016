#ifndef INC_6_854_PROJECT_HELPERS_H
#define INC_6_854_PROJECT_HELPERS_H

#define PI 3.14159265

double l2norm(double a[], double b[], int size);

int loadData(char* path, double* values);

double angle(double* vector);

void positive_directions(double* vector, double* overlap, double* directions);

#endif //INC_6_854_PROJECT_HELPERS_H
