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
    check(exp_answer, naive_diameter(points), "naive diam2d");
}

void test_monotonicity_simple_triangle() {
    std::vector<Point> points = {{2.0, 0.0},
                                 {0.0, 1.0},
                                 {0.0, -1.0}};
    std::vector<int> exp_answer = {2, 2, 2};

    check(exp_answer, naive_monotonicity_2d(points), "naive monotonicity_simple_triangle");
}

void test_monotonicity_11gon() {
    std::vector<Point> data = load_csv_data("data/11-gon.csv");
    std::vector<int> exp_answer = {6, 7, 8, 9, 10, 10, 10, 10, 10, 10, 10};

    check(exp_answer, naive_monotonicity_2d(data), "naive monotonicity_11gon");
    check(exp_answer, bce_monotonicity_2d(data), "bce monotonicty_11gon");
}

int main() {
    test_diam2d();
    test_monotonicity_simple_triangle();
    test_monotonicity_11gon();
    return 0;
}

