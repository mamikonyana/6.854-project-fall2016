#include <stdio.h>
#include "../src/helpers.h"
#include "../src/naive.h"
#include "../src/bce.h"

int main(int argc, char *argv[]) {
    printf("argc %d\n", argc);
    auto data_file = argc >= 2 ? argv[1] : "data/gaussian_1k.csv";
    auto output_filename = argc == 3 ? argv[2] : "bce_monotonicity.txt";

    printf("loading %s..\n", argv[1]);
    std::vector<Point> data = load_csv_data(data_file);
    printf("loaded %lu points\n", data.size());

    clock_t start = clock();
    printf("start = %ld\n", start);
    std::vector<int> naive_a = bce_monotonicity_2d(data);
    clock_t end = clock();
    FILE* outfile = fopen(output_filename, "w");
    printf("size %lu\n", naive_a.size());
    for (int i = 0; i < naive_a.size(); i++) {
        fprintf(outfile, "%d\n", naive_a[i]);
    }
    fclose(outfile);
    printf("runtime = %f milliseconds \n", 1000 * (double) (end - start) / CLOCKS_PER_SEC);

}


