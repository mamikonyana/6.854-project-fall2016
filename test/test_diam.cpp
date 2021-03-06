#include <printf.h>
#include <vector>
#include "../src/helpers.h"
#include "../src/naive.h"
#include "../src/chan_prat_2016.h"
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


void test_13gon_55() {

    std::vector<Point> points = load_csv_data("data/13-gon-radius0.55.csv");

    std::vector<int> exp_answer = {4, 5, 6, 7, 8, 9, 10, 11, 12, 12, 12, 12, 12};
    check_vectors(exp_answer, naive_diameter(points), "13gon_55 naive");
    check_vectors(exp_answer, chan_prat_diameter_2d(points), "13gon_55 Chan, Prat");
}


void test_file(std::string filename, std::vector<int> exp_answer) {

    std::vector<Point> points = load_csv_data(filename);

    check_vectors(exp_answer, naive_diameter(points), filename + " naive");
    check_vectors(exp_answer, chan_prat_diameter_2d(points), filename + " Chan, Prat");
}

int main() {
    test_diam2d();
    test_13gon_55();
    test_file("data/7_circles.csv", {3, 3, 6, 6, 6, 6, 6});
    test_file("data/segfault.csv", {6, 6, 6, 6, 6, 6, 6});
    return 0;
}

