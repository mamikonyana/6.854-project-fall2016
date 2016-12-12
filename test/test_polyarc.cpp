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

    printf("PASS: test_direction\n\n");
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
    PolyArc pa1 = PolyArc(Point2D{data[0][0], data[0][1]}, 0);
    PolyArc pa2 = PolyArc(Point2D{data[1][0], data[1][1]}, 1);
    PolyArc pa3 = PolyArc(Point2D{data[2][0], data[2][1]}, 2);

    PolyArc pa12 = pa1.intersect(pa2);
    std::vector<Vertex> vertices;
    vertices = pa12.getVertices();


    assert(vertices.size() == 4);
    assert(vertices[0].location == (Point2D{-0.450000000, 0.000000000}));
    assert(vertices[1].location == (Point2D{0.577137635, 0.999631707}));
    assert(vertices[2].location == (Point2D{0.725000000, 0.476313972}));
    assert(vertices[3].location == (Point2D{-0.302137635, -0.523317734}));

    PolyArc pa123 = pa12.intersect(pa3);
    vertices = pa123.getVertices();

    // for (auto& v : vertices) {
    //     printf("%.9f %.9f\n", v.location.x, v.location.y);
    // }

    assert(vertices.size() == 4);

    assert(vertices[0].location == (Point2D{-0.450000000, 0.000000000}));
    assert(vertices[1].location == (Point2D{-0.302137635, 0.523317734}));
    assert(vertices[2].location == (Point2D{0.604275270, -0.000000000}));
    assert(vertices[3].location == (Point2D{-0.302137635, -0.523317734}));

    printf("PASS: intersect_circles_3_normal\n\n");
}

void test_intersect_circles_3_normal_non_pairwise() {
    printf("START: intersect_circles_3_normal_non_pairwise\n");

    std::vector<Point> data = load_csv_data("data/3-circles-normal-non-pairwise.csv");
    PolyArc pa1 = PolyArc(Point2D{data[0][0], data[0][1]}, 0);
    PolyArc pa2 = PolyArc(Point2D{data[1][0], data[1][1]}, 1);
    PolyArc pa3 = PolyArc(Point2D{data[2][0], data[2][1]}, 2);

    PolyArc pa13 = pa1.intersect(pa3);

    PolyArc pa123 = pa2.intersect(pa13);

    auto vertices = pa123.getVertices();
    assert(vertices.size() == 4);

    assert(vertices[0].location == (Point2D{1.000000000, 0.000000000}));
    assert(vertices[1].location == (Point2D{1.500000000, 0.866025404}));
    assert(vertices[2].location == (Point2D{2.000000000, 0.000000000}));
    assert(vertices[3].location == (Point2D{1.500000000, -0.866025404}));

    printf("PASS: intersect_circles_3_normal_non_pairwise\n\n");
}

void test_intersect_circles_3_degenerate() {
    printf("START: intersect_circles_3_degenerate\n");

    std::vector<Point> data = load_csv_data("data/3-circles-degenerate.csv");
    PolyArc pa1 = PolyArc(Point2D{data[0][0], data[0][1]}, 0);
    PolyArc pa2 = PolyArc(Point2D{data[1][0], data[1][1]}, 1);
    PolyArc pa3 = PolyArc(Point2D{data[2][0], data[2][1]}, 2);

    PolyArc pa12 = pa1.intersect(pa2);

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

/**
 * 10 circles on x axis, 0.5 apart from each other, starting at origin
 */
void test_contains_manual() {
    printf("START: test_contains_manual\n");

    double center_delta = 0.5;
    double offset = center_delta / 2;
    double h = std::sqrt(1 - offset * offset);
    std::vector<Vertex> upper(0);
    std::vector<Vertex> lower(0);
    upper.push_back(Vertex{Point2D{-1, 0}, Point2D{0., 0.}, 0});
    lower.push_back(Vertex{Point2D{-1, 0}, Point2D{0., 0.}, 0});
    for (int i = 1; i < 10; i++) {
        auto center = Point2D{i * center_delta, 0};
        double x = -offset + i * center_delta;
        upper.push_back(Vertex{Point2D{x, h}, center, i});
        lower.push_back(Vertex{Point2D{x, -h}, center, i});
    }
    double center_x = 9. * center_delta;
    upper.push_back(Vertex{Point2D{1. + center_x, 0}, Point2D{center_x, 0.}, 10});
    lower.push_back(Vertex{Point2D{1. + center_x, 0}, Point2D{center_x, 0.}, 10});

    PolyArc polyArc = PolyArc(upper, lower);

    assert(polyArc.contains(Point2D{0., 0.}));
    assert(polyArc.contains(Point2D{3.3, 0.}));
    assert(polyArc.contains(Point2D{3.3, 1.}) == false);
    assert(polyArc.contains(Point2D{2.25, -h + 0.01}));
    assert(polyArc.contains(Point2D{2.25, -h - 0.01}) == false);
    assert(polyArc.contains(Point2D{4.4, 0.}));
    assert(polyArc.contains(Point2D{5.6, 0.}) == false);
    printf("PASS: test_contains_manual\n\n");
}

void test_contains_triangular() {
    printf("START: test_contains_triangular\n");
    std::vector<Point> data = load_csv_data("data/triangle-radius0.55.csv");

    PolyArc pa1 = PolyArc(Point2D{data[0][0], data[0][1]}, 0);

    PolyArc pa2 = PolyArc(Point2D{data[1][0], data[1][1]}, 1);
    PolyArc pa3 = PolyArc(Point2D{data[2][0], data[2][1]}, 2);

    assert(pa1.contains(Point2D{0., 0.}));
    assert(pa1.contains(Point2D{0., 2}) == false);
    assert(pa1.contains(Point2D{0., -2}) == false);

    PolyArc pa12 = pa1.intersect(pa2);
    assert(pa12.contains(Point2D{0., 0.}));
    assert(pa12.contains(Point2D{1., 2.}) == false);

    PolyArc pa123 = pa12.intersect(pa3);
    assert(pa123.contains(Point2D{0.12, 0.12}));
    assert(pa123.contains(Point2D{-0.12, 0.2}));
    assert(pa12.contains(Point2D{1., 2.}) == false);

    printf("PASS: test_contains_triangular\n\n");
}

void test_intersect_envelopes_basic() {
    printf("START: test_intersect_envelopes_basic\n");
    Vertex v1 = {Point2D{0, 0}, Point2D{1, 0}, 0};
    Vertex v2 = {Point2D{1, 0}, Point2D{2, 0}, 1};
    Vertex v3 = {Point2D{2, 0}, Point2D{1, 0}, 0};
    Vertex v4 = {Point2D{3, 0}, Point2D{2, 0}, 1};

    auto upper1 = std::vector<Vertex>{v1, v3};
    auto upper2 = std::vector<Vertex>{v2, v4};

    auto res = intersect_envelopes(upper1, upper2, -1);

    // for (auto& v : res) {
    //     printf("%.2f %.2f %.2f %.2f\n", v.location.x, v.location.y, v.arch_center.x, v.arch_center.y);
    // }

    assert(res.size() == 3);
    assert(res[0].location == (Point2D{1, 0}));
    assert(res[1].location == (Point2D{1.5, sqrt(3.0) / 2}));
    assert(res[2].location == (Point2D{2, 0}));

    res = intersect_envelopes(upper1, upper2, 1);

    // for (auto& v : res) {
    //     printf("%.2f %.2f %.2f %.2f\n", v.location.x, v.location.y, v.arch_center.x, v.arch_center.y);
    // }

    assert(res.size() == 3);
    assert(res[0].location == (Point2D{1, 0}));
    assert(res[1].location == (Point2D{1.5, -sqrt(3.0) / 2}));
    assert(res[2].location == (Point2D{2, 0}));

    printf("PASS: test_intersect_envelopes_basic\n\n");
}

void test_intersect_envelopes_below() {
    printf("START: test_intersect_envelopes_below\n");
    Vertex v1 = {Point2D{1, 2}, Point2D{2, 2}, 0};
    Vertex v2 = {Point2D{3, 2}, Point2D{2, 2}, 0};

    Vertex v3 = {Point2D{1.5, 1}, Point2D{2.5, 1}, 1};
    Vertex v4 = {Point2D{3.5, 1}, Point2D{2.5, 1}, 1};

    auto upper1 = std::vector<Vertex>{v1, v2};
    auto upper2 = std::vector<Vertex>{v3, v4};

    auto res = intersect_envelopes(upper1, upper2, -1);
    // for (auto& v : res) {
    //     printf("%.2f %.2f %.2f %.2f\n", v.location.x, v.location.y, v.arch_center.x, v.arch_center.y);
    // }

    assert(res.size() == 2);
    assert(res[0].location == (Point2D{1.5, 1}));
    assert(res[1].location == (Point2D{3, 1 + sqrt(3.0) / 2}));
    printf("PASS: test_intersect_envelopes_below\n\n");
}

void test_intersect_envelopes_empty() {
    printf("START: test_intersect_envelopes_empty\n");
    Vertex v1 = {Point2D{0, 0}, Point2D{1, 0}, 0};
    Vertex v2 = {Point2D{2, 0}, Point2D{1, 0}, 0};

    Vertex v3 = {Point2D{3, 0}, Point2D{4, 0}, 1};
    Vertex v4 = {Point2D{5, 0}, Point2D{4, 0}, 1};

    auto upper1 = std::vector<Vertex>{v1, v2};
    auto upper2 = std::vector<Vertex>{v3, v4};

    auto res = intersect_envelopes(upper1, upper2, -1);

    // for (auto& v : res) {
    //     printf("%.2f %.2f %.2f %.2f\n", v.location.x, v.location.y, v.arch_center.x, v.arch_center.y);
    // }

    assert(res.size() == 0);
    printf("PASS: test_intersect_envelopes_empty\n\n");
}

void test_intersect_envelopes_degenerate() {
    printf("START: test_intersect_envelopes_degenerate\n");
    Vertex v1 = {Point2D{0, 0}, Point2D{1, 0}, 0};
    Vertex v2 = {Point2D{2, 0}, Point2D{1, 0}, 0};

    Vertex v3 = {Point2D{2, 0}, Point2D{3, 0}, 1};
    Vertex v4 = {Point2D{4, 0}, Point2D{3, 0}, 1};

    auto upper1 = std::vector<Vertex>{v1, v2};
    auto upper2 = std::vector<Vertex>{v3, v4};

    auto res = intersect_envelopes(upper1, upper2, -1);

    // for (auto& v : res) {
    //     printf("%.2f %.2f %.2f %.2f\n", v.location.x, v.location.y, v.arch_center.x, v.arch_center.y);
    // }

    assert(res.size() == 1);
    assert(res[0].location == (Point2D{2, 0}));
    printf("PASS: test_intersect_envelopes_degenerate\n\n");
}

void test_intersect_lower_upper_no_inside_points() {
    printf("START: test_intersect_lower_upper_no_inside_points\n");

    Vertex v1 = {Point2D{1, 0}, Point2D{2, 0}, 0};
    Vertex v2 = {Point2D{3, 0}, Point2D{2, 0}, 0};

    Vertex v3 = {Point2D{1, 1.5}, Point2D{2, 1.5}, 1};
    Vertex v4 = {Point2D{3, 1.5}, Point2D{2, 1.5}, 1};

    auto upper = std::vector<Vertex>{v1, v2};
    auto lower = std::vector<Vertex>{v3, v4};

    auto res = intersect_upper_lower(upper, lower);

    assert(res.first.size() == 2);
    assert(res.second.size() == 2);
    assert(res.first[0].location == (Point2D{1.338562172, 0.75000000}));
    assert(res.first[1].location == (Point2D{2.661437828, 0.75000000}));

    assert(res.second[0].location == (Point2D{1.338562172, 0.75000000}));
    assert(res.second[1].location == (Point2D{2.661437828, 0.75000000}));

    printf("PASS: test_intersect_lower_upper_no_inside_points\n\n");
}

void test_intersect_lower_upper_degenerate() {
    printf("START: test_intersect_lower_upper_degenerate\n");

    Vertex v1 = {Point2D{1, 0}, Point2D{2, 0}, 0};
    Vertex v2 = {Point2D{3, 0}, Point2D{2, 0}, 0};

    Vertex v3 = {Point2D{1, 2}, Point2D{2, 2}, 1};
    Vertex v4 = {Point2D{3, 2}, Point2D{2, 2}, 1};

    auto upper = std::vector<Vertex>{v1, v2};
    auto lower = std::vector<Vertex>{v3, v4};

    auto res = intersect_upper_lower(upper, lower);

    // printf("%lu\n", res.first.size());
    // for (auto& v : res.first) {
    //     printf("%.2f %.2f %.2f %.2f\n", v.location.x, v.location.y, v.arch_center.x, v.arch_center.y);
    // }

    assert(res.first.size() == 1);
    assert(res.first[0].location == (Point2D{2, 1}));

    printf("PASS: test_intersect_lower_upper_degenerate\n\n");
}

void test_intersect_lower_upper_empty() {
    printf("START: test_intersect_lower_upper_empty\n");

    Vertex v1 = {Point2D{1, 0}, Point2D{2, 0}, 0};
    Vertex v2 = {Point2D{3, 0}, Point2D{2, 0}, 0};

    Vertex v3 = {Point2D{0.5, 2}, Point2D{1.5, 2}, 1};
    Vertex v4 = {Point2D{2.5, 2}, Point2D{1.5, 2}, 1};

    auto upper = std::vector< Vertex >{v1, v2};
    auto lower = std::vector< Vertex >{v3, v4};

    auto res = intersect_upper_lower(upper, lower);

    printf("%lu\n", res.first.size());
    for (auto& v : res.first) {
        print_vertex(v);
    }

    assert(res.first.size() == 0);
    assert(res.second.size() == 0);

    printf("PASS: test_intersect_lower_upper_empty\n\n");
}

void test_notfoundassert() {
    printf("START: notfoundassert\n");
    std::vector<Point> data = load_csv_data("data/notfoundassert.csv");

    PolyArc pa0 = PolyArc(Point2D{data[0][0], data[0][1]}, 0);
    PolyArc pa1 = PolyArc(Point2D{data[1][0], data[1][1]}, 1);
    PolyArc pa2 = PolyArc(Point2D{data[2][0], data[2][1]}, 2);
    PolyArc pa3 = PolyArc(Point2D{data[3][0], data[3][1]}, 3);

    // printf("single polyarcs - done\n");

    PolyArc pa01 = pa0.intersect(pa1);

    // printf("pa01 - done\n");

    PolyArc pa23 = pa2.intersect(pa3);

    // printf("pa23 - done\n");

    PolyArc pa0123 = pa01.intersect(pa23);

    printf("PASS: notfoundassert\n\n");
}

void test_segfault() {
    printf("START: segfault\n");
    std::vector<Point> data = load_csv_data("data/notfoundassert.csv");

    std::vector<PolyArc> single(7);
    for (int i = 0; i < data.size(); ++i) {
        single[i] = PolyArc(Point2D{data[i][0], data[i][1]}, i);
        // printf("done single %d\n", i);
    }

    std::vector<PolyArc> pairwise(4);
    for (int i = 0; i < 3; ++i) {
        pairwise[i] = single[2 * i].intersect(single[2 * i + 1]);
        // printf("done pairwise %d - %d\n", 2 * i, 2 * i + 1);
    }
    pairwise[3] = single[6];

    std::vector<PolyArc> quad(2);
    for (int i = 0; i < 2; ++i) {
        quad[i] = pairwise[2 * i].intersect(pairwise[2 * i + 1]);
        // printf("done quad %d - %d\n", 4 * i, std::min(4 * i + 3, 6));
    }

    quad[0].intersect(quad[1]);

    printf("PASS: segfaultt\n\n");
}

int main() {
    test_contains_manual();
    test_contains_triangular();
    test_direction();
    test_intersect_circles();
    test_intersect_circles_3_normal();
    test_intersect_circles_3_normal_non_pairwise();
    test_intersect_circles_3_degenerate();
    test_intersect_envelopes_basic();
    test_intersect_envelopes_below();
    test_intersect_envelopes_empty();
    test_intersect_envelopes_degenerate();
    test_intersect_lower_upper_degenerate();
    test_intersect_lower_upper_no_inside_points();
    test_intersect_lower_upper_empty();
    test_notfoundassert();
    test_segfault();
    return 0;
}

