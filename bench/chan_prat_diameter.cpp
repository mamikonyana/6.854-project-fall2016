#include <stdio.h>
#include "../src/helpers.h"
#include "../src/naive.h"
#include "../src/chan_prat_2016.h"

int main(int argc, char *argv[]) {
    printf("argc %d\n", argc);
    auto data_file = argc >= 2 ? argv[1] : "data/gaussian_1k.csv";
    auto output_filename = argc == 3 ? argv[2] : "chain_prat_diameter.txt";

    printf("loading %s..\n", argv[1]);
    std::vector<Point> data = load_csv_data(data_file);
    printf("loaded %lu points\n", data.size());

    clock_t start = clock();
    printf("start = %ld\n", start);
    std::vector<int> cp_a = chan_prat_diameter_2d(data);
    clock_t end = clock();
    FILE* outfile = fopen(output_filename, "w");
    printf("size %lu\n", cp_a.size());
    for (int i = 0; i < cp_a.size(); i++) {
        fprintf(outfile, "%d\n", cp_a[i]);
    }
    fclose(outfile);
    printf("runtime = %f milliseconds \n", 1000 * (double) (end - start) / CLOCKS_PER_SEC);

}


