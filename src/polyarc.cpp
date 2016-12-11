#include <vector>
#include <assert.h>

#include "helpers.h"
#include "polyarc.h"

PolyArc::PolyArc() {
}

PolyArc::PolyArc(Point2D center) {
    mIsCircle = true;
    singleCircle = center;
}

PolyArc::PolyArc(Vertex v) {
    upper.push_back(v);
    lower.push_back(v);
    mIsCircle = false;
}

PolyArc::PolyArc(Vertex v1, Vertex v2) {
    if (v1.location.x > v2.location.x + EPS ||
        (fequal(v1.location.x, v2.location.x) && v1.location.y > v2.location.y)) {
        std::swap(v1, v2);
    }
    mIsCircle = false;
    lower.push_back(v1);
    lower.push_back(v2);
    upper.push_back(v1);
    upper.push_back(v2);
}

bool PolyArc::isEmpty() {
    return !mIsCircle && upper.size() == 0;
}

bool PolyArc::isPoint() {
    return !mIsCircle && upper.size() == 1;
}

bool PolyArc::isCircle() {
    return mIsCircle;
}

int PolyArc::nArcs() {
    if (isEmpty()) {
        return -1;
    }
    if (mIsCircle) {
        return 1;
    }
    if (isPoint()) {
        return 0;
    }

    return upper.size() - 1 + lower.size() - 1;
}

PolyArc PolyArc::intersect(PolyArc other) {
    if (isEmpty() || other.isEmpty()) {
        return PolyArc();
    }

    if (isPoint() && other.isPoint()) {
        if (fequal(upper[0].location.x, other.upper[0].location.x) &&
            fequal(upper[0].location.y, other.upper[0].location.y)) {
            return PolyArc(upper[0]);
        }
        return PolyArc();
    }

    if (isPoint()) {
        return other.intersect(*this);
    }

    if (other.isPoint()) {
        Point2D& pt = other.upper[0].location;
        if (isCircle()) {
            if (circle_contains(singleCircle, pt)) {
                return other;
            }
            return PolyArc();
        }

        for (auto& vertex : upper) {
            if (!circle_contains(vertex.arch_center, vertex.location)) {
                return PolyArc();
            }
        }
        for (auto& vertex : lower) {
            if (!circle_contains(vertex.arch_center, vertex.location)) {
                return PolyArc();
            }
        }

        return other;
    }

    if (isCircle() && other.isCircle()) {
        if (singleCircle == other.singleCircle) {
            return *this;
        }
        auto intersections = intersect_circles(singleCircle, other.singleCircle);
        if (intersections.size() == 0) {
            return PolyArc();
        }

        if (intersections.size() == 1) {
            Vertex vertex = {intersections[0], singleCircle, -1};
            return PolyArc(vertex);
        }

        return PolyArc(Vertex{intersections[0], singleCircle, 0}, Vertex{intersections[1], other.singleCircle, 0});
    }

    if (isCircle()) {
        return other.intersect(*this);
    }

    // now we know that either
    // * this is a 2 vertex polyarc and other is a circle OR
    // * both are normal polyarcs

    // if (other.isCircle()) {
    //     assert(nArcs() == 2);

    //     Point2D a  = upper[0].location;
    //     Point2D c1 = upper[0].arch_center;
    //     Point2D b = lower[1].location;
    //     Point2D c2 = lower[1].arch_center;

    //     // printf("arc1: %.2f %.2f ;  %.2f %.2f;  %.2f %.2f\n", c1.x, c1.y, a.x, a.y, b.x, b.y);
    //     // printf("arc2: %.2f %.2f ;  %.2f %.2f;  %.2f %.2f\n", c2.x, c2.y, b.x, b.y, a.x, a.y);

    //     auto intersections1 = intersect_circle_arc(other.singleCircle, c1, a, b);
    //     auto intersections2 = intersect_circle_arc(other.singleCircle, c2, b, a);

    //     // printf("intersections1\n");
    //     // for (auto x : intersections1) {
    //     //     printf("%.2f %.2f\n", x.x, x.y);
    //     // }

    //     // printf("intersections2\n");
    //     // for (auto x : intersections2) {
    //     //     printf("%.2f %.2f\n", x.x, x.y);
    //     // }

    //     assert(intersections1.size() + intersections2.size() <= 2);

    //     if (intersections1.size() == 0 && intersections2.size() == 0) {
    //         if (circle_contains(other.singleCircle, a)) {
    //             assert(circle_contains(other.singleCircle, b));
    //             return *this;
    //         }
    //         return PolyArc();
    //     }

    //     if (intersections2.size() > intersections1.size()) { // cases (1, 0); (2, 0)
    //         std::swap(intersections1, intersections2);
    //         std::swap(c1, c2);
    //     }

    //     if (intersections1.size() == 2) {
    //         if (direction(c1, intersections1[0], intersections1[1]) > 0) {
    //             std::swap(intersections1[0], intersections1[1]);
    //         }
    //         return PolyArc(Vertex{intersections1[0], c1, 0},
    //                        Vertex{intersections1[1], other.singleCircle, 0});
    //     }

    //     if (intersections1.size() == 1 && intersections2.size() == 0) { // the second one doesn't intersect
    //         return PolyArc(Vertex{intersections1[0], other.singleCircle, -1});
    //     }

    //     // both intersect once; in this case the swap of intersections above wouldn't happen
    //     auto& p1 = intersections1[0];
    //     auto& p2 = intersections2[0];

    //     if (p1 == p2) {
    //         return PolyArc(Vertex{p1, other.singleCircle, 0});
    //     }

    //     auto res = PolyArc();
    //     if (circle_contains(other.singleCircle, a)) {
    //         res.vertices.push_back(Vertex{a, c1, 0});
    //         res.vertices.push_back(Vertex{p1, other.singleCircle, 0});
    //         res.vertices.push_back(Vertex{p2, c2, 0});
    //     } else if (circle_contains(other.singleCircle, b)) {
    //         res.vertices.push_back(Vertex{b, c2, 0});
    //         res.vertices.push_back(Vertex{p2, other.singleCircle, 0});
    //         res.vertices.push_back(Vertex{p1, c1, 0});
    //     } else {
    //         assert(false);
    //     }
    //     res.reorder();
    //     return res;
    // }

    // TODO

    return PolyArc();
}

// void PolyArc::reorder() {
//     int leftmost = 0;
//     for (int i = 1; i < vertices.size(); ++i) {
//         if (vertices[i].location.x < vertices[leftmost].location.x) {
//             leftmost = i;
//         }
//     }
// 
//     std::rotate(vertices.begin(), vertices.begin() + leftmost, vertices.end());
// }

std::vector<Vertex> PolyArc::getVertices() {
    if (isEmpty()) {
        return std::vector< Vertex > ();
    }
    if (isPoint()) {
        return upper;
    }
    std::vector< Vertex > vertices(upper.size() + lower.size() - 2);
    vertices.insert(vertices.begin(), upper.begin(), upper.end());
    vertices.insert(vertices.end(), lower.rbegin() + 1, lower.rend() - 1);
    return vertices;
}

bool PolyArc::contains(Point2D query_point) {
    return false;
}

////////////// helpers ////////////////

int direction(Point2D origin, Point2D first, Point2D second) {
    double cross_prod = (first.x - origin.x) * (second.y - origin.y) - (first.y - origin.y) * (second.x - origin.x);
    if (cross_prod < -EPS) {
        return -1;
    }
    if (cross_prod > EPS) {
        return 1;
    }
    return 0;
}

std::vector< Point2D > intersect_circles(Point2D c1, Point2D c2) {
    // http://e-maxx.ru/algo/circles_intersection
    assert(!(c1 == c2)); // assume the centers are different

    // shift c1 to origin
    c2.x -= c1.x;
    c2.y -= c1.y;

    double a = -2 * c2.x;
    double b = -2 * c2.y;
    double c = c2.x * c2.x + c2.y * c2.y;

    Point2D p0 = {-a * c / (a * a + b * b), -b * c / (a * a + b * b)};
    if (c * c > (a * a + b * b) + EPS) {
        return std::vector< Point2D >();
    }
    if (fequal(c * c, a * a + b * b)) {
        p0.x += c1.x;
        p0.y += c1.y;
        return std::vector< Point2D >(1, p0);
    }
    double d = 1- c * c / (a * a + b * b);
    double mult = sqrt(d / (a * a + b * b));
    double ax, ay, bx, by;
    Point2D p1 = {p0.x + b * mult, p0.y - a * mult};
    Point2D p2 = {p0.x - b * mult, p0.y + a * mult};

    p1.x += c1.x;
    p1.y += c1.y;
    p2.x += c1.x;
    p2.y += c1.y;

    if (direction(c1, p1, p2) > 0) {
        std::swap(p1, p2);
    }

    return std::vector< Point2D >({p1, p2});
}

bool circle_contains(Point2D center, Point2D pt) {
    return (center.x - pt.x) * (center.x - pt.x) + (center.y - pt.y) * (center.y - pt.y) <= 1;
}

bool on_arc(Point2D center, Point2D a, Point2D b, Point2D pt) {
    return direction(center, a, pt) < 0 && direction(center, pt, b) < 0;
}

std::vector< Point2D > intersect_circle_arc(Point2D center, Point2D arc_center, Point2D a, Point2D b) {
    auto circle_intersections = intersect_circles(center, arc_center);
    std::vector< Point2D > res;

    for (Point2D& pt : circle_intersections) {
        if (on_arc(arc_center, a, b, pt)) {
            res.push_back(pt);
        }
    }

    return res;
}

