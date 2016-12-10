#include <printf.h>
#include <vector>

#include <assert.h>

#include "../src/helpers.h"
#include "../src/naive.h"
#include "../src/bce.h"

#include "check.h"

void test_diam2d() {
    std::vector<Point> points = {{0.0, 0.0},
                                 {0.2, 0.2},
                                 {0.5, 0.5},
                                 {1.0, 1.0},
                                 {2.0, 2.0},
                                 {2.5, 2.5}};

    std::vector<int> exp_answer = {2, 2, 3, 3, 5, 5};
    check_vectors(exp_answer, naive_diameter(points), "naive diam2d");
}

int main() {
    test_diam2d();
    return 0;
}

