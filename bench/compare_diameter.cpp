#include <stdio.h>
#include <stdlib.h>
#include "../src/helpers.h"
#include "../src/naive.h"
#include "../src/bce.h"
#include "../src/chan_prat_2016.h"

int main(int argc, char *argv[]) {
    printf("argc %d\n", argc);
    FILE *outfile = fopen("bench/compare_diameter.csv", "w");
    fprintf(outfile, "num_points, Chan/Prat,Naive\n");
    for (int i = 1; i < argc; i++) {
        auto data_file = argv[i];
        printf("loading %s..\n", argv[i]);
        std::vector<Point> data = load_csv_data(data_file);
        printf("loaded %lu points\n", data.size());

        clock_t cp_start = clock();
        auto cp_ans = chan_prat_diameter_2d(data);
        clock_t cp_end = clock();
        auto naive_a = naive_diameter(data);
        clock_t naive_end = clock();
        printf("%f milliseconds, and %f milliseconds\n",
               1000 * (double) (cp_end - cp_start) / CLOCKS_PER_SEC,
               1000 * (double) (naive_end - cp_end) / CLOCKS_PER_SEC);
        fprintf(outfile, "%lu,%.1f,%.1f\n",
                data.size(),
                1000 * (double) (cp_end - cp_start) / CLOCKS_PER_SEC,
                1000 * (double) (naive_end - cp_end) / CLOCKS_PER_SEC);
        // Random checks
        printf("Random spot checks..\n");
        for (int _ = 0; _ < 10; _++) {
            int x = rand() % data.size();
            printf("[%d]: %d == %d, ", x, naive_a[x], cp_ans[x]);
            if (naive_a[x] != cp_ans[x]) {
                printf("Houston we've got a problem!\n");
                // return -1;
            }
        }
        printf("\n");

        // printf("All checks..\n");
        // bool works = true;
        // for (int i = 0; i < data.size(); ++i) {
        //     if (naive_a[i] != cp_ans[i]) {
        //         printf("Houston we've got a problem!\n");
        //         works = false;
        //     }
        // }
        // if (works) {
        //     printf("Heuston we don't have problems!");
        // }
        printf("\n");
    }
    fclose(outfile);
}
