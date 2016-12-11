#include "../src/chan_prat_2016.h"
#include "../src/range_tree.h"

void test_range_tree_construct() {
    std::vector<Point> points = {{0.0, 1.0},
                                 {0.1, 1.1},
                                 {1.2, 1.2}};
    RangeTree rt = RangeTree(points);
    printf("PASS: range_tree_construct\n");
}

int main() {
    test_range_tree_construct();
    return 0;
}
