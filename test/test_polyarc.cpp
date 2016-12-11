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

    printf("PASS: test_intersect_circles\n\n");
}

void test_intersect_circles_3_normal() {
    printf("START: intersect_circles_3_normal\n");

    std::vector<Point> data = load_csv_data("data/triangle-radius0.55.csv");
    PolyArc pa1 = PolyArc(Point2D{data[0][0], data[0][1]});
    PolyArc pa2 = PolyArc(Point2D{data[1][0], data[1][1]});
    PolyArc pa3 = PolyArc(Point2D{data[2][0], data[2][1]});

    PolyArc pa12 = pa1.intersect(pa2);
    std::vector<Vertex> vertices;
    vertices = pa12.getVertices();
    assert(vertices.size() == 2);
    assert_equal(vertices[0].location.x, -0.302138, 1e-5);
    assert_equal(vertices[0].location.y, -0.523318, 1e-5);
    assert_equal(vertices[1].location.x, 0.577138, 1e-5);
    assert_equal(vertices[1].location.y, 0.999632, 1e-5);

    PolyArc pa123 = pa12.intersect(pa3);
    vertices = pa123.getVertices();
    assert(vertices.size() == 3);

    assert_equal(vertices[0].location.x, -0.302138, 1e-5);
    assert_equal(vertices[0].location.y, -0.523318, 1e-5);
    assert_equal(vertices[1].location.x, -0.302138, 1e-5);
    assert_equal(vertices[1].location.y, 0.523318, 1e-5);
    assert_equal(vertices[2].location.x, 0.604275, 1e-5);
    assert_equal(vertices[2].location.y, 0.000000, 1e-5);
    // printf("vertices %f %f %f %f %f %f\n", vertices[0].location.x, vertices[0].location.y, vertices[1].location.x, vertices[1].location.y, vertices[2].location.x, vertices[2].location.y);
    printf("PASS: intersect_circles_3_normal\n\n");
}

void test_intersect_circles_3_normal_non_pairwise() {
    printf("START: intersect_circles_3_normal_non_pairwise\n");

    std::vector< Point > data = load_csv_data("data/3-circles-normal-non-pairwise.csv");
    PolyArc pa1 = PolyArc(Point2D{data[0][0], data[0][1]});
    PolyArc pa2 = PolyArc(Point2D{data[1][0], data[1][1]});
    PolyArc pa3 = PolyArc(Point2D{data[2][0], data[2][1]});

    PolyArc pa13  = pa1.intersect(pa3);

    PolyArc pa123 = pa2.intersect(pa13);

    auto vertices = pa123.getVertices();
    assert(vertices.size() == 2);

    // printf("vertices %f %f %f %f\n", vertices[0].location.x, vertices[0].location.y, vertices[1].location.x, vertices[1].location.y);
    assert_equal(vertices[0].location.x, 1.5, 1e-5);
    assert_equal(vertices[0].location.y, 0.866025, 1e-5);
    assert_equal(vertices[1].location.x, 1.5, 1e-5);
    assert_equal(vertices[1].location.y, -0.866025, 1e-5);

    printf("PASS: intersect_circles_3_normal_non_pairwise\n\n");
}

void test_intersect_circles_3_degenerate() {
    printf("START: intersect_circles_3_degenerate\n");

    std::vector< Point > data = load_csv_data("data/3-circles-degenerate.csv");
    PolyArc pa1 = PolyArc(Point2D{data[0][0], data[0][1]});
    PolyArc pa2 = PolyArc(Point2D{data[1][0], data[1][1]});
    PolyArc pa3 = PolyArc(Point2D{data[2][0], data[2][1]});

    PolyArc pa12  = pa1.intersect(pa2);

    PolyArc pa123 = pa12.intersect(pa3);

    auto vertices = pa123.getVertices();
    assert(vertices.size() == 1);

    assert_equal(vertices[0].location.x, 0.0, 1e-5);
    assert_equal(vertices[0].location.y, 0.0, 1e-5);

    PolyArc pa13 = pa3.intersect(pa1);
    pa123 = pa13.intersect(pa2);

    vertices = pa123.getVertices();
    assert(vertices.size() == 1);

    assert_equal(vertices[0].location.x, 0.0, 1e-5);
    assert_equal(vertices[0].location.y, 0.0, 1e-5);

    printf("PASS: intersect_circles_3_degenerate\n\n");
}


void test_contains() {
    std::vector<Point> data = load_csv_data("data/triangle-radius0.55.csv");

    PolyArc pa1 = PolyArc(Point2D{data[0][0], data[0][1]});

    PolyArc pa2 = PolyArc(Point2D{data[1][0], data[1][1]});
    PolyArc pa3 = PolyArc(Point2D{data[2][0], data[2][1]});

    assert(pa1.contains(Point2D{0., 0.}));
    assert(pa1.contains(Point2D{0., 2}) == false);
    assert(pa1.contains(Point2D{0., -2}) == false);

    // PolyArc pa12 = pa1.intersect(pa2);
    // assert(pa12.contains(Point2D{0., 0.}));
    // assert(pa12.contains(Point2D{1., 2.}) == false);

    // PolyArc pa123 = pa12.intersect(pa3);
    // assert(pa123.contains(Point2D{0.12, 0.12}));
    // assert(pa123.contains(Point2D{-0.12, 0.2}));
    // assert(pa12.contains(Point2D{1., 2.}) == false);

    printf("PASS: test_contains\n\n");
}

int main() {
    test_contains();
    test_direction();
    test_intersect_circles();
    test_intersect_circles_3_normal();
    test_intersect_circles_3_normal_non_pairwise();
    test_intersect_circles_3_degenerate();
    return 0;
}

