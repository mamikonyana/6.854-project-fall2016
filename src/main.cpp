#include <stdio.h>
#include <assert.h>
#include "helpers.h"

int main() {
    Position p1 = {10, 20};
    Position p2 = {11, 21};
    printf("%.2f\n", difference_l2norm(p1, p2));
    printf("loading data/11-gon.csv..\n");
    std::vector<Position> data = load_csv_data("data/11-gon.csv");
    printf("loaded %lu points\n", data.size());
    /*
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
    */

    // double dir[2];

    // double v1[4] = {0, 0, 1, 0};
    // positive_directions(v1, NULL, dir);

    // printf("%.1f, %.1f\n", dir[0] * 180/ PI , dir[1] * 180/ PI );

    // printf("loading data/11-gon.csv..\n");
    // double data[100];
    // int dataSize = loadData("data/11-gon.csv", data);
    // const int Dim = 2;
    // const int size = 11;
    // assert(dataSize == 22);
    // int length = dataSize / Dim;
    // int naive_a[11];
    // naive_monotonicity_2d(data, length, naive_a);
    // for (int i = 0; i < size; i++) {
    //     printf("%d\n", naive_a[i]);
    // }

}


