#include <vector>
#include <assert.h>

#include "helpers.h"
#include "polyarc.h"

PolyArc::PolyArc() {
}

PolyArc::PolyArc(Point2D center) {
    Vertex left = {Point2D{center.x - 1, center.y}, center, -1};
    Vertex right = {Point2D{center.x + 1, center.y}, center, -1};
    upper.push_back(left);
    upper.push_back(right);
    lower.push_back(left);
    lower.push_back(right);
}

bool PolyArc::isEmpty() {
    return upper.size() == 0;
}

bool PolyArc::isPoint() {
    return upper.size() == 1;
}

int PolyArc::nArcs() {
    if (isEmpty() || isPoint()) {
        return 0;
    }

    return upper.size() - 1 + lower.size() - 1;
}

PolyArc PolyArc::intersect(PolyArc other) {
    if (isEmpty() || other.isEmpty()) {
        return *this;
    }

    if (isPoint() && other.isPoint()) {
        if (upper[0].location == other.upper[0].location) {
            return *this;
        }
        return PolyArc();
    }

    if (isPoint()) {
        return other.intersect(*this);
    }

    if (other.isPoint()) {
        Point2D& pt = other.upper[0].location;

        for (auto &vertex : upper) {
            if (!circle_contains(vertex.arch_center, vertex.location)) {
                return PolyArc();
            }
        }
        for (auto &vertex : lower) {
            if (!circle_contains(vertex.arch_center, vertex.location)) {
                return PolyArc();
            }
        }

        return other;
    }

    std::vector< Vertex > upperIntersect = intersect_envelopes(upper, other.upper, -1);
    std::vector< Vertex > lowerIntersect = intersect_envelopes(lower, other.lower,  1);

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
        return std::vector<Vertex>();
    }
    if (isPoint()) {
        return upper;
    }
    std::vector<Vertex> vertices(upper.size() + lower.size() - 2);
    vertices.insert(vertices.begin(), upper.begin(), upper.end());
    vertices.insert(vertices.end(), lower.rbegin() + 1, lower.rend() - 1);
    return vertices;
}


bool PolyArc::contains(Point2D query_point) {
    int upper_left = find_neighbours(upper, query_point.x);
    if (upper_left == -1) {
        return false;
    }
    if (!circle_contains(upper[upper_left].arch_center, query_point)) {
        return false;
    }
    int lower_left = find_neighbours(lower, query_point.x);
    // lower_left can't be -1, because upper_left is not -1.
    if (!circle_contains(lower[lower_left].arch_center, query_point)) {
        return false;
    }
    return true;
}

/**
 * @param vector
 * @param x
 * @return return -1, if x has only one neighbour. otherwise index of the left neighbour.
 */
int PolyArc::find_neighbours(std::vector<Vertex> vector, double query_x) {
    // TODO: make efficient (binary search style).
    if (vector[0].location.x > query_x) {
        return -1; // No left neighbour.
    }
    for (int i = 1; i < vector.size(); i++) {
        if (vector[i].location.x > query_x) {
            // Found right neighbour.
            return i - 1;
        }
    }
    return -1; // No right neighbour.
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

std::vector<Point2D> intersect_circles(Point2D c1, Point2D c2) {
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
        return std::vector<Point2D>();
    }
    if (fequal(c * c, a * a + b * b)) {
        p0.x += c1.x;
        p0.y += c1.y;
        return std::vector<Point2D>(1, p0);
    }
    double d = 1 - c * c / (a * a + b * b);
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

    return std::vector<Point2D>({p1, p2});
}

bool circle_contains(Point2D center, Point2D pt) {
    return (center.x - pt.x) * (center.x - pt.x) + (center.y - pt.y) * (center.y - pt.y) <= 1;
}

bool on_arc(Point2D center, Point2D a, Point2D b, Point2D pt) {
    return direction(center, a, pt) < 0 && direction(center, pt, b) < 0;
}

std::vector< Point2D > intersect_circle_arc(Point2D center, Point2D arc_center, Point2D a, Point2D b) {
    // assumes arcs are given in clockwise order
    auto circle_intersections = intersect_circles(center, arc_center);
    std::vector<Point2D> res;

    for (Point2D &pt : circle_intersections) {
        if (on_arc(arc_center, a, b, pt)) {
            res.push_back(pt);
        }
    }

    return res;
}

std::pair< Point2D, bool > intersect_arcs(Point2D c1, Point2D a1, Point2D b1, Point2D c2, Point2D a2, Point2D b2) {
    // assumes arcs are given in clockwise order
    auto arc_circle = intersect_circle_arc(c1, c2, a2, b2);
    Point2D res;
    bool found = false;
    for (auto pt : arc_circle) {
        if (on_arc(c1, a1, b1, pt)) {
            assert(!found);
            found = true;
            res = pt;
        }
    }
    return std::make_pair(res, found);
}

std::vector< Vertex > intersect_envelopes(std::vector< Vertex >& upper1, std::vector< Vertex >& upper2, int dir) {
    std::vector< Vertex > res;

    std::vector< std::vector< Vertex > > envelopes = {upper1, upper2};
    std::vector< int > front(2, 0);

    int lower = -1;

    while (front[0] < envelopes[0].size() && front[1] < envelopes[1].size()) {
        printf("\n==============\n");
        int s = envelopes[0][front[0]].location.x < envelopes[1][front[1]].location.x ? 0 : 1;

        printf("front = %d %d, s = %d\n", front[0], front[1], s);
        if (front[s] == 0 && front[1 - s] == 0) {
            front[s]++;
            continue;
        }

        Point2D curr = envelopes[s][front[s]].location;
        Point2D ac = envelopes[1 - s][front[1 - s] - 1].arch_center;
        
        Point2D other = {curr.x, ac.y - dir * sqrt(1 - (curr.x - ac.x) * (curr.x - ac.x))};

        printf("curr = (%.2f %.2f); other = (%.2f, %.2f)\n", curr.x, curr.y, other.x, other.y);
        // TODO x1 == x2

        Vertex new_vertex;
        int new_lower = -1;
        if (fequal(curr.y, other.y)) {
            if (direction(curr, envelopes[s][front[s]].location, envelopes[1 - s][front[1 - s]].location) == dir) {
                new_vertex = Vertex{other, ac, envelopes[1 - s][front[1 - s] - 1].circle_index};
                new_lower = 1 - s;
            } else {
                new_vertex = Vertex{curr, envelopes[s][front[s]].arch_center, envelopes[s][front[s]].circle_index};
                new_lower = s;
            }
        } else {
            if (curr.y < other.y) {
                new_vertex = Vertex{curr, envelopes[s][front[s]].arch_center, envelopes[s][front[s]].circle_index};
                new_lower = s;
            } else {
                new_vertex = Vertex{other, ac, envelopes[1 - s][front[1 - s] - 1].circle_index};
                new_lower = 1 - s;
            }
        }

        printf("lower %d, new_lower = %d\n", lower, new_lower);

        if (lower != -1 && new_lower != lower) {
            std::pair< Point2D, bool > new_intersection;
            if (dir == -1) {
                new_intersection = intersect_arcs(envelopes[s][front[s] - 1].arch_center,
                                                  envelopes[s][front[s] - 1].location,
                                                  envelopes[s][front[s]].location,

                                                  envelopes[1 - s][front[1 - s] - 1].arch_center,
                                                  envelopes[1 - s][front[1 - s] - 1].location,
                                                  envelopes[1 - s][front[1 - s]].location);
            } else {
                new_intersection = intersect_arcs(envelopes[s][front[s] - 1].arch_center,
                                                  envelopes[s][front[s]].location,
                                                  envelopes[s][front[s] - 1].location,

                                                  envelopes[1 - s][front[1 - s] - 1].arch_center,
                                                  envelopes[1 - s][front[1 - s]].location,
                                                  envelopes[1 - s][front[1 - s] - 1].location);
            }
            assert(new_intersection.second);
            printf("new_intersection: (%.2f, %.2f)\n", new_intersection.first.x, new_intersection.first.y);

//           auto& prev = *res.rbegin();
//           if (prev.circle_index == envelopes[new_lower][front[new_lower] - 1].circle_index) {
//               assert(prev.arch_center == envelopes[new_lower][front[new_lower] - 1].arch_center);
//           } else {
                res.push_back(Vertex{ new_intersection.first,
                                      envelopes[new_lower][front[new_lower] - 1].arch_center,
                                      envelopes[new_lower][front[new_lower] - 1].circle_index });
            //}
        }

//        auto& prev = *res.rbegin();
//        if (prev.circle_index == new_vertex.circle_index) {
//            assert(prev.arch_center == new_vertex.arch_center);
//        } else {
            res.push_back(new_vertex);
        //}

        lower = new_lower;
        front[s]++;
    }

    return res;
}

