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
    std::vector<Vertex> upper;
    std::vector<Vertex> lower;

    int find_neighbours(std::vector<Vertex> vector, double x);

    // void reorder();

public:
    PolyArc();

    PolyArc(Point2D center, int circle_index);

    // Used for testing.
    PolyArc(std::vector<Vertex> upper, std::vector<Vertex> lower) {
        this->upper = upper;
        this->lower = lower;
    }

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

std::vector<Point2D> intersect_circles(Point2D c1, Point2D c2);

std::vector<Point2D> intersect_circle_arc(Point2D center, Point2D arc_center, Point2D a, Point2D b);

bool circle_contains(Point2D center, Point2D pt);

std::vector< Vertex > intersect_envelopes(std::vector< Vertex >& upper1, std::vector< Vertex >& upper2, int dir);

#endif // POLYARC_H

