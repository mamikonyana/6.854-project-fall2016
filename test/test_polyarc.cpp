#include <printf.h>
#include <vector>

#include <assert.h>

#include "../src/helpers.h"
#include "../src/polyarc.h"

#include "check.h"

void test_direction() {
    printf("START: test_direction\n");
    Point2D o1 = {0, 0};
    Point2D p1 = {0, 1};
    Point2D q1 = {1, 0};

    assert(direction(o1, p1, q1) < 0);
    assert(direction(o1, q1, p1) > 0);

    Point2D o2 = {5, 5};
    Point2D p2 = {6, 7};
    Point2D q2 = {4, 3};

    assert(direction(o2, p2, q2) == 0);

    printf("PASS: test_direction\n");
}

void test_intersect_circles() {
    printf("START: test_intersect_circles\n");

    Point2D c1 = {1, 1};
    Point2D c2 = {2, 2};
    Point2D c3 = {3, 1};
    Point2D c4 = {4, 4};


    auto res = intersect_circles(c2, c1);
    assert(res.size() == 2);
    assert(fequal(res[0].x, 2) && fequal(res[0].y, 1));
    assert(fequal(res[1].x, 1) && fequal(res[1].y, 2));

    res = intersect_circles(c1, c3);
    assert(res.size() == 1);
    assert(fequal(res[0].x, 2) && fequal(res[0].y, 1));

    assert(intersect_circles(c1, c4).size() == 0);

    printf("PASS: test_intersect_circles\n");
}

int main() {
    test_direction();
    test_intersect_circles();
    return 0;
}

