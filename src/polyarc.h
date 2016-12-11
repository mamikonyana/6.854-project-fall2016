#ifndef POLYARC_H
#define POLYARC_H

#include <vector>

struct Point2D {
    double x, y;

    bool operator == (Point2D other) {
        return fequal(x, other.x) && fequal(y, other.y);
    }
};

struct Vertex {
    Point2D location;
    Point2D arch_center;
    int circle_index; // index of circle
};

class PolyArc {
private:
    std::vector<Vertex> vertices;

    bool mIsCircle;
    Point2D singleCircle;

    PolyArc(Vertex vertex);

    PolyArc(Vertex v1, Vertex v2);

    void reorder();
public:
    PolyArc();

    PolyArc(Point2D center);

    bool isCircle();

    bool isEmpty();

    bool isPoint(); // if only 1 point

    bool contains(Point2D query_point);

    int nArcs();

    PolyArc intersect(PolyArc other);

    std::vector<Vertex> getVertices();
};

//////// helpers //////

// return -1(1), if first to second is (counter)clockwise wrt origin. Otherwise, 0
int direction(Point2D origin, Point2D first, Point2D second);

std::vector< Point2D > intersect_circles(Point2D c1, Point2D c2);

std::vector< Point2D > intersect_circle_arc(Point2D center, Point2D arc_center, Point2D a, Point2D b);

bool circle_contains(Point2D center, Point2D pt);

#endif // POLYARC_H

