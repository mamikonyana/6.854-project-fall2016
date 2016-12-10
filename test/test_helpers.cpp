#include <stdio.h>
#include <assert.h>
#include <cmath>

#include "../src/helpers.h"

void assert_equal(double d1, double d2, double prec) {
    assert(std::abs(d1 - d2) < prec);
}

void test_relative_angle() {
    Point p1 = {0, 0};
    Point p2 = {1, 1};
    assert_equal(relative_angle(p1, p2), PI / 4, 1e-5);
    Point p3 = {0, 0.42264973081037438};
    assert_equal(relative_angle(p2, p3), PI + PI / 6, 1e-5);
    printf("PASS: relative_angle\n");
}

int main() {
    test_relative_angle();
    return 0;
}

