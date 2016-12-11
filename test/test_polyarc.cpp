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

void test_intersect_circles_3() {
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
    // assert_equal(vertices[0].location.x, -0.302138, 1e-5);
    // assert_equal(vertices[0].location.y, -0.523318, 1e-5);
    // assert_equal(vertices[1].location.x, 0.577138, 1e-5);
    // assert_equal(vertices[1].location.y, 0.999632, 1e-5);
    // assert_equal(vertices[2].location.x, 0.577138, 1e-5);
    // assert_equal(vertices[2].location.y, 0.999632, 1e-5);
    printf("vertices %f %f %f %f %f %f", vertices[0].location.x, vertices[0].location.y, vertices[1].location.x, vertices[1].location.y, vertices[2].location.x, vertices[2].location.y);

}

int main() {
    test_direction();
    test_intersect_circles();
    test_intersect_circles_3();
    return 0;
}

