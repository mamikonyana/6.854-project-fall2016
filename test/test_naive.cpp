#include <printf.h>
#include <vector>

#include <assert.h>

#include "../src/helpers.h"
#include "../src/naive.h"


void test_diam2d() {
    std::vector<Point> points = {{0.0, 0.0},
                                 {0.2, 0.2},
                                 {0.5, 0.5},
                                 {1.0, 1.0},
                                 {2.0, 2.0},
                                 {2.5, 2.5}};

    std::vector<int> answer = naive_diameter(points);
    std::vector<int> exp_answer = {2, 2, 3, 3, 5, 5};
    assert(answer == exp_answer);
    printf("PASS: diam2d\n");
}

void test_monotonicity_11gon() {
    std::vector<Point> data = load_csv_data("data/11-gon.csv");
    std::vector<int> naive_a = naive_monotonicity_2d(data);
    for (int i = 0; i < naive_a.size(); i++) {
        printf("%d\n", naive_a[i]);
    }
}

int main() {
    test_diam2d();
    test_monotonicity_11gon();
    return 0;
}

