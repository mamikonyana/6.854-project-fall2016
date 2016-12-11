#include <stdio.h>
#include "helpers.h"
#include "naive.h"

int main(int argc, char *argv[]) {
    printf("argc %d\n", argc);
    std::string data_file;
    data_file = argc == 2 ? argv[1] : "data/gaussian_1k.csv";

    printf("loading %s..\n", argv[1]);
    std::vector<Point> data = load_csv_data(data_file);
    printf("loaded %lu points\n", data.size());

    clock_t start = clock();
    printf("start = %ld\n", start);
    std::vector<int> naive_a = naive_diameter(data);
    clock_t end = clock();
    for (int i = 0; i < 10; i++) {
        printf("%d\n", naive_a[i]);
    }
    printf("runtime = %f milliseconds \n", 1000 * (double) (end - start) / CLOCKS_PER_SEC);

}


