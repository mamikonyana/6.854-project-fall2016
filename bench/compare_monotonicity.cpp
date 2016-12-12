#include <stdio.h>
#include <stdlib.h>
#include "../src/helpers.h"
#include "../src/naive.h"
#include "../src/bce.h"

int main(int argc, char *argv[]) {
    printf("argc %d\n", argc);
    FILE *outfile = fopen("bench/compare_monotonicity.csv", "w");
    fprintf(outfile, "BCE,Naive\n");
    for (int i = 1; i < argc; i++) {
        auto data_file = argv[i];
        printf("loading %s..\n", argv[i]);
        std::vector<Point> data = load_csv_data(data_file);
        printf("loaded %lu points\n", data.size());

        clock_t bce_start = clock();
        auto bce_a = bce_monotonicity_2d(data);
        clock_t bce_end = clock();
        auto naive_a = naive_monotonicity_2d(data);
        clock_t naive_end = clock();
        printf("%f milliseconds, and %f milliseconds\n",
               1000 * (double) (bce_end - bce_start) / CLOCKS_PER_SEC,
               1000 * (double) (naive_end - bce_end) / CLOCKS_PER_SEC);
        fprintf(outfile, "%f,%f\n",
               1000 * (double) (bce_end - bce_start) / CLOCKS_PER_SEC,
               1000 * (double) (naive_end - bce_end) / CLOCKS_PER_SEC);
        // Random checks
        printf("Random spot checks..\n");
        for (int _ = 0; _ < 10; _++) {
            int x = rand() % data.size();
            printf("[%d]: %d == %d, ", x, naive_a[x], bce_a[x]);
            if (naive_a[x] != bce_a[x]) {
                printf("Houston we've got a problem!");
                // return -1;
            }
        }
        printf("\n");
    }
    fclose(outfile);
}
