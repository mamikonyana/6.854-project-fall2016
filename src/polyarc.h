#ifndef POLYARC_H
#define POLYARC_H

#include <vector>

struct Point2D {
    double x, y;
};

struct Vertex {
    Point2D location;
    Point2D arch_center;
    int circle_index; // index of circle
};

class PolyArc {
private:
    std::vector<Vertex> vertices;

public:
    PolyArc intersect(PolyArc other);

    PolyArc intersect(Point2D circle);

    static PolyArc fromCircles(Point2D c1, Point2D c2);
};

//////// helpers //////

// return -1(1), if first to second is (counter)clockwise wrt origin. Otherwise, 0
int direction(Point2D origin, Point2D first, Point2D second);

std::vector< Point2D > intersect_circles(Point2D c1, Point2D c2);

#endif // POLYARC_H

