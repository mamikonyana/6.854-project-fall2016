#include <stdio.h>
#include <assert.h>
#include <cmath>

#include "../src/helpers.h"

void assert_equal(double d1, double d2, double prec) {
    assert(std::abs(d1 - d2) < prec);
}

void test_relative_angle() {
    Point origin = {0, 0};
    Point p2 = {1, 1};
    assert_equal(relative_angle(origin, p2), PI / 4, 1e-5);
    Point p3 = {0, 0.42264973081037438};
    assert_equal(relative_angle(p2, p3), PI + PI / 6, 1e-5);
    Point p4 = {-0.19866933079506111, 0.98006657784124163}; // cos, sin of 0.2 + PI/2
    assert_equal(relative_angle(origin, p4), 0.2 + PI / 2, 1e-5);
    Point p5 = {0.29552020666133966, -0.95533648912560598}; // cos, sin of 0.3 - PI/2
    assert_equal(relative_angle(origin, p5), 0.3 + 3 * PI / 2, 1e-5);
    printf("PASS: relative_angle\n");
}

void test_positive_directions() {
    Point origin = {0, 0};
    Point p2 = {1, 1};
    std::pair<double, double> range;
    range = positive_directions(origin, p2);
    assert_equal(range.first, 2 * PI - PI / 4, 1e-5);
    assert_equal(range.second, PI / 2 + PI / 4, 1e-5);
    Point p3 = {0, 0.42264973081037438};
    range = positive_directions(p2, p3);
    assert_equal(range.first, PI / 2 + PI / 6, 1e-5);
    assert_equal(range.second, PI * 3 / 2 + PI / 6, 1e-5);

    Point p4 = {-0.19866933079506111, 0.98006657784124163}; // cos, sin of 0.2 + PI/2
    range = positive_directions(origin, p4);
    assert_equal(range.first, 0.2, 1e-5);
    assert_equal(range.second, 0.2 + PI, 1e-5);
    Point p5 = {0.29552020666133966, -0.95533648912560598}; // cos, sin of 0.3 - PI/2
    std::pair<double, double> range2;
    range2 = positive_directions(origin, p5);
    assert_equal(range2.first, 0.3 + PI, 1e-5);
    assert_equal(range2.second, 0.3, 1e-5);
    printf("PASS: positive_directions\n");
}

void test_range_intersect() {
    Point origin = {0, 0};
    Point p4 = {-0.19866933079506111, 0.98006657784124163}; // cos, sin of 0.2 + PI/2
    std::pair<double, double> range = positive_directions(origin, p4);
    assert_equal(range.first, 0.2, 1e-5);
    assert_equal(range.second, 0.2 + PI, 1e-5);
    Point p5 = {0.29552020666133966, -0.95533648912560598}; // cos, sin of 0.3 - PI/2
    std::pair<double, double> range2 = positive_directions(origin, p5);
    assert_equal(range2.first, 0.3 + PI, 1e-5);
    assert_equal(range2.second, 0.3, 1e-5);

    std::pair<double, double> intersect;
    intersect = range_intersect(range, range2);
    assert_equal(intersect.first, 0.2, 1e-5);
    assert_equal(intersect.second, 0.3, 1e-5);

    std::pair<double, double> range3 = {0.0, PI};
    std::pair<double, double> range4 = {0.2, PI + 0.1};
    intersect = range_intersect(range3, range4);
    assert_equal(intersect.first, 0.2, 1e-5);
    assert_equal(intersect.second, PI, 1e-5);

    std::pair<double, double> range5 = {0.7, 0.9};
    std::pair<double, double> range6 = {0.2, 0.4};
    intersect = range_intersect(range5, range6);
    assert_equal(intersect.first, -1, 1e-5);

    std::pair<double, double> range7 = {PI * 135 / 180, PI * 315 / 180};
    std::pair<double, double> range8 = {PI * 315 / 180, PI * 135 / 180};
    intersect = range_intersect(range7, range8);
    assert_equal(intersect.first, -1, 1e-5);

    std::pair<double, double> range9  = {PI * 90 / 180, PI * 270 / 180};
    std::pair<double, double> range10 = {PI * 270 / 180, PI * 90 / 180};
    intersect = range_intersect(range9, range10);
    assert_equal(intersect.first, -1, 1e-5);
    printf("PASS: range_intersect\n");
}

int main() {
    test_relative_angle();
    test_positive_directions();
    test_range_intersect();
    return 0;
}

