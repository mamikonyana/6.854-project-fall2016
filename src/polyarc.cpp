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
    vertices.push_back(v);
    mIsCircle = false;
}

PolyArc::PolyArc(Vertex v1, Vertex v2) {
    if (v1.location.x > v2.location.x) {
        std::swap(v1, v2);
    }
    mIsCircle = false;
    vertices.push_back(v1);
    vertices.push_back(v2);
}

bool PolyArc::isEmpty() {
    return !mIsCircle && vertices.size() == 0;
}

bool PolyArc::isDegenerate() {
    return !mIsCircle && vertices.size() == 1;
}

bool PolyArc::isCircle() {
    return mIsCircle;
}

PolyArc PolyArc::intersect(PolyArc other) {
    if (isCircle() && other.isCircle()) {
        auto intersections = intersect_circles(singleCircle, other.singleCircle);
        if (intersections.size() == 0) {
            return PolyArc();
        }

        if (intersections.size() == 1) {
            Vertex vertex = {intersections[0], singleCircle, -1};
            return PolyArc(vertex);
        }

        PolyArc(Vertex{intersections[0], singleCircle, 0}, Vertex{intersections[1], other.singleCircle, 0});
    }

    // TODO

    return PolyArc();
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
    assert(!fequal(c1.x, c2.x) || !fequal(c1.y, c2.y)); // assume the centers are different

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

