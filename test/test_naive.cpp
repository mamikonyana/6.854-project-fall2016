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

int main() {
    test_diam2d();
    return 0;
}

