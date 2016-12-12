#include <printf.h>
#include <vector>

#include <assert.h>

#include "../src/helpers.h"
#include "../src/naive.h"
#include "../src/bce.h"

#include "check.h"

void test_monotonicity_simple_triangle() {
    std::vector<Point> points = {{2.0, 0.0},
                                 {0.0, 1.0},
                                 {0.0, -1.0}};
    std::vector<int> exp_answer = {2, 2, 2};

    check_vectors(exp_answer, naive_monotonicity_2d(points), "naive monotonicity_simple_triangle");
}

void test_monotonicity_1d_movement() {

    std::vector<Point> points = {{0.0, 0.0},
                                 {1.1, 0.0},
                                 {1.2, 0.0},
                                 {-1.4, 0.0},
                                 {1.5, 0.0}};
    std::vector<int> exp_answer = {2, 2, 3, 4, 4};

    check_vectors(exp_answer, naive_monotonicity_2d(points), "naive monotonicity_1d");
    check_vectors(exp_answer, bce_monotonicity_2d(points), "bce monotonicity_1d");
}

void test_monotonicity_1d_tilted_movement() {
    std::vector<Point> points = {{0.0, 0.0},
                                 {1.1, 1.1},
                                 {1.2, 1.2},
                                 {-1.4, -1.4},
                                 {1.5, 1.5}};
    std::vector<int> exp_answer = {2, 2, 3, 4, 4};

    check_vectors(exp_answer, naive_monotonicity_2d(points), "naive monotonicity_1d_tilted");
    check_vectors(exp_answer, bce_monotonicity_2d(points), "bce monotonicity_1d_tilted");

}

void test_monotonicity_11gon() {
    std::vector<Point> data = load_csv_data("data/11-gon.csv");
    std::vector<int> exp_answer = {6, 7, 8, 9, 10, 10, 10, 10, 10, 10, 10};

    check_vectors(exp_answer, naive_monotonicity_2d(data), "naive monotonicity_11gon");
    check_vectors(exp_answer, bce_monotonicity_2d(data), "bce monotonicty_11gon");
}


void test_monotonicity_bce_vs_naive(std::string file) {
    std::vector<Point> data = load_csv_data(file.c_str());

    auto naive_answer = naive_monotonicity_2d(data);
    auto bce_answer   = bce_monotonicity_2d(data);

    check_vectors(naive_answer, bce_answer, "bce vs naive: " + file);

    double total_jump = 0;
    for (int i = 0; i < bce_answer.size(); ++i) {
        total_jump += bce_answer[i] - i + 1;
    }
    // printf("    average jump %.2f", total_jump / bce_answer.size());

    printf("\n");
}

int main() {
    // test_monotonicity_simple_triangle();
    test_monotonicity_1d_movement();
    printf("\n");
    printf("DIVIDE\n");
    printf("\n");
    test_monotonicity_1d_tilted_movement();
    // test_monotonicity_11gon();
    // test_monotonicity_bce_vs_naive("data/20_random_walk_2d-0.3.csv");
    // test_monotonicity_bce_vs_naive("data/random_walkish.csv");
    // test_monotonicity_bce_vs_naive("data/gaussian_20.csv");
    // test_monotonicity_bce_vs_naive("data/gaussian_200.csv");
    // test_monotonicity_bce_vs_naive("data/gaussian_2000.csv");
    return 0;
}

