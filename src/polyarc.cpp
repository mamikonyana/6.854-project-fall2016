#include <vector>
#include <assert.h>

#include "helpers.h"
#include "polyarc.h"

PolyArc::PolyArc() {
}

PolyArc::PolyArc(Point2D center, int circle_index) {
    Vertex left = {Point2D{center.x - 1, center.y}, center, circle_index};
    Vertex right = {Point2D{center.x + 1, center.y}, center, circle_index};
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
        Point2D &pt = other.upper[0].location;

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

    std::vector<Vertex> upperIntersect = intersect_envelopes(upper, other.upper, -1);

    // printf("Upper vertices\n");
    // for (auto& v : upperIntersect) {
    //     print_vertex(v);
    // }
    // printf("\n");

    std::vector<Vertex> lowerIntersect = intersect_envelopes(lower, other.lower, 1);

    // printf("Lower vertices\n");
    // for (auto& v : lowerIntersect) {
    //     print_vertex(v);
    // }
    // printf("\n");

    auto upperLowerIntersect = intersect_upper_lower(upperIntersect, lowerIntersect);

    PolyArc res = PolyArc();
    res.upper = upperLowerIntersect.first;
    // printf("Res upper\n");
    // for (auto& v : res.upper) {
    //     print_vertex(v);
    // }
    // printf("\n");

    res.lower = upperLowerIntersect.second;
    // printf("Res lower\n");
    // for (auto& v : res.lower) {
    //     print_vertex(v);
    // }
    // printf("\n");

    return res;
}

std::vector<Vertex> PolyArc::getVertices() {
    if (isEmpty()) {
        return std::vector<Vertex>();
    }
    if (isPoint()) {
        return upper;
    }

    std::vector<Vertex> vertices;
    vertices.insert(vertices.begin(), upper.begin(), upper.end());
    vertices.insert(vertices.end(), lower.rbegin() + 1, lower.rend() - 1);
    return vertices;
}


bool PolyArc::contains(Point2D query_point) {
    if (this->isEmpty()) {
        return false;
    }
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
    if (vector[0].location.x > query_x) {
        return -1; // No left neighbour.
    }
    int a = 0;
    int b = vector.size() - 1;
    while (a != b) {
        if (b - a == 1) {
            if (vector[a].location.x <= query_x && vector[b].location.x >= query_x) {
                return a;
            } else {
                return -1;
            }
        }
        int i = (b + a) / 2;
        if (vector[i].location.x > query_x) {
            b = i;
        } else {
            a = i;
        }
    }
    return -1; // It should not get here.
    // if (b == vector.size() - 1) {
    //     return -1; // No right neighbour.
    // } else {
    //     return b;
    // }

    // for (int i = 1; i < vector.size(); i++) {
    //     if (vector[i].location.x > query_x) {
    //         // Found right neighbour.
    //         return i - 1;
    //     }
    // }
    // return -1; // No right neighbour.
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

std::vector<Point2D> intersect_circle_arc(Point2D center, Point2D arc_center, Point2D a, Point2D b) {
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

std::vector< Point2D > intersect_arcs(Point2D c1, Point2D a1, Point2D b1, Point2D c2, Point2D a2, Point2D b2) {
    // assumes arcs are given in clockwise order
    auto arc_circle = intersect_circle_arc(c1, c2, a2, b2);

    std::vector< Point2D > res;
    for (auto pt : arc_circle) {
        if (on_arc(c1, a1, b1, pt)) {
            res.push_back(pt);
        }
    }
    return res;
}

std::vector<Vertex> intersect_envelopes(std::vector<Vertex> &upper1, std::vector<Vertex> &upper2, int dir) {
    std::vector<Vertex> res;

    std::vector<std::vector<Vertex> > envelopes = {upper1, upper2};
    std::vector<int> front(2, 0);

    int lower = -1;
    double lastX;

    while (front[0] < envelopes[0].size() && front[1] < envelopes[1].size()) {
        // printf("\n==============\n");
        if (envelopes[0][front[0]].location == envelopes[1][front[1]].location) {
            lastX = envelopes[0][front[0]].location.x;
            if (front[0] == envelopes[0].size() - 1 || front[1] == envelopes[1].size()) {
                lower = 0;
                break;
            }
            if (direction(envelopes[0][front[0]].location,
                          envelopes[0][front[0] + 1].location,
                          envelopes[1][front[1] + 1].location) == dir) {
                res.push_back(envelopes[1][front[1]]);
                lower = 1;
            } else {
                res.push_back(envelopes[0][front[0]]);
                lower = 0;
            }
            front[0]++;
            front[1]++;
            continue;
        }

        int s = envelopes[0][front[0]].location.x < envelopes[1][front[1]].location.x ? 0 : 1;
        Point2D curr = envelopes[s][front[s]].location;

        lastX = curr.x;

        // printf("front = %d %d, s = %d\n", front[0], front[1], s);
        // TODO x1 == x2
        if (front[1 - s] == 0) {
            front[s]++;
            continue;
        }

        Point2D ac = envelopes[1 - s][front[1 - s] - 1].arch_center;

        Point2D other = {curr.x, ac.y - dir * sqrt(1 - (curr.x - ac.x) * (curr.x - ac.x))};

        // printf("curr = (%.2f %.2f); other = (%.2f, %.2f)\n", curr.x, curr.y, other.x, other.y);

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
            if (dir * (curr.y - other.y) > 0) {
                new_vertex = Vertex{curr, envelopes[s][front[s]].arch_center, envelopes[s][front[s]].circle_index};
                new_lower = s;
            } else {
                new_vertex = Vertex{other, ac, envelopes[1 - s][front[1 - s] - 1].circle_index};
                new_lower = 1 - s;
            }
        }

        // printf("lower %d, new_lower = %d\n", lower, new_lower);
        // printf("new_vertex %.2f %.2f\n", new_vertex.location.x, new_vertex.location.y);

        if (lower != -1 && new_lower != lower) {
            // std::pair< Point2D, bool > new_intersection;
            std::vector< Point2D > new_intersection;
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
            assert(new_intersection.size() == 1);
            // printf("new_intersection: (%.2f, %.2f)\n", new_intersection.first.x, new_intersection.first.y);

            auto &prev = res[res.size() - 1];
            if (prev.circle_index == envelopes[new_lower][front[new_lower] - 1].circle_index) {
                assert(prev.arch_center == envelopes[new_lower][front[new_lower] - 1].arch_center);
            } else {
                res.push_back(Vertex{ new_intersection[0],
                                      envelopes[new_lower][front[new_lower] - 1].arch_center,
                                      envelopes[new_lower][front[new_lower] - 1].circle_index });
            }
        }

        if (res.size() > 0) {
            auto &prev = *res.rbegin();
            if (prev.circle_index == new_vertex.circle_index) {
                assert(prev.arch_center == new_vertex.arch_center);
            } else {
                res.push_back(new_vertex);
            }
        } else {
            res.push_back(new_vertex);
        }

        lower = new_lower;
        front[s]++;
    }
    if (lower != -1) {
        auto new_vertex = envelopes[lower][front[lower] - 1];
        auto &ac = envelopes[lower][front[lower] - 1].arch_center;
        double lastY = ac.y - dir * sqrt(1 - (lastX - ac.x) * (lastX - ac.x));
        res.push_back(Vertex{Point2D{lastX, lastY}, ac, envelopes[lower][front[lower] - 1].circle_index});
    }

    return res;
}

std::pair<std::vector<Vertex>, std::vector<Vertex> >
intersect_upper_lower(std::vector<Vertex> upper, std::vector<Vertex> lower) {
    auto res = std::make_pair(std::vector<Vertex>(), std::vector<Vertex>());

    int state = 0;
    int u = 0, l = 0;

    while (state < 2 && u < upper.size() && l < lower.size()) {
        // printf("%d: %d %d\n", state, u, l);
        // printf("upper: %.2f %.2f\n", upper[u].location.x, upper[u].location.y);
        // printf("lower: %.2f %.2f\n", lower[l].location.x, lower[l].location.y);
        if (upper[u].location == lower[l].location) {
            // printf("equal\n");
            res.first.push_back(upper[u]);
            res.second.push_back(lower[l]);
            state++;
            u++;
            l++;
            continue;
        }

        // std::pair< Point2D, bool > new_intersection;
        std::vector< Point2D > new_intersection;
        if (u > 0 && l > 0) {
            // printf("new_intersection - start\n");
            // printf("circles %d %d\n", upper[u - 1].circle_index, lower[l - 1].circle_index);
            if (upper[u - 1].circle_index != lower[l - 1].circle_index) {
                new_intersection = intersect_arcs(upper[u - 1].arch_center,
                                                  upper[u - 1].location,
                                                  upper[u].location,

                                                  lower[l - 1].arch_center,
                                                  lower[l].location,
                                                  lower[l - 1].location);

                if (intersect_circles(upper[u - 1].arch_center, lower[l - 1].arch_center).size() == 1) {
                    new_intersection.push_back(new_intersection[0]);
                }

                if (new_intersection.size() == 2) {
                    if (new_intersection[0] == new_intersection[1]) {
                        return std::make_pair(std::vector< Vertex >{Vertex{new_intersection[0], upper[u - 1].arch_center, upper[u - 1].circle_index}},
                                              std::vector< Vertex >{Vertex{new_intersection[0], lower[l - 1].arch_center, lower[l - 1].circle_index}});
                    }
                    if (new_intersection[0].x > new_intersection[1].x) {
                        std::swap(new_intersection[0], new_intersection[1]);
                    }
                    return std::make_pair(std::vector< Vertex >{Vertex{new_intersection[0], upper[u - 1].arch_center, upper[u - 1].circle_index},
                                                           Vertex{new_intersection[1], upper[u - 1].arch_center, upper[u - 1].circle_index}},
                                          std::vector< Vertex >{Vertex{new_intersection[0], lower[l - 1].arch_center, lower[l - 1].circle_index},
                                                           Vertex{new_intersection[1], lower[l - 1].arch_center, lower[l - 1].circle_index}});

                }
            }
            // printf("new_intersection %d: %.2f %.2f\n", new_intersection.second, new_intersection.first.x, new_intersection.first.y);
        }

        if (fequal(upper[u].location.x, lower[l].location.x)) {
            if ((state == 0 && upper[u].location.y > lower[l].location.y) ||
                (state == 1 && upper[u].location.y < lower[l].location.y)) {
                assert(new_intersection.size() == 1);

                res.first.push_back (Vertex{new_intersection[0], upper[u - 1].arch_center, upper[u - 1].circle_index});
                res.second.push_back(Vertex{new_intersection[0], lower[l - 1].arch_center, lower[l - 1].circle_index});
                state++;
            }
            if (state == 1) {
                res.first.push_back(upper[u]);
                res.second.push_back(lower[l]);
            }
            u++;
            l++;
        } else if (upper[u].location.x < lower[l].location.x) {
            auto &ac = lower[l - 1].arch_center;
            double &x = upper[u].location.x;

            double y = ac.y - sqrt(1 - (ac.x - x) * (ac.x - x));

            if (fequal(y, upper[u].location.y)) {
                res.first.push_back(upper[u]);
                res.second.push_back(Vertex{upper[u].location, lower[l - 1].arch_center, lower[l - 1].circle_index});
                state++;
            } else if (y < upper[u].location.y) {
                if (state == 0) {
                    assert(new_intersection.size() == 1);
                    res.first.push_back (Vertex{new_intersection[0], upper[u - 1].arch_center, upper[u - 1].circle_index});
                    res.second.push_back(Vertex{new_intersection[0], lower[l - 1].arch_center, lower[l - 1].circle_index});

                    state++;
                }
                res.first.push_back(upper[u]);
            } else {
                if (state == 1) {
                    assert(new_intersection.size() == 1);
                    res.first.push_back (Vertex{new_intersection[0], upper[u - 1].arch_center, upper[u - 1].circle_index});
                    res.second.push_back(Vertex{new_intersection[0], lower[l - 1].arch_center, lower[l - 1].circle_index});

                    state++;
                }
            }
            u++;
        } else { // upper[u].location.x > lower[l].location.x  ######## should be symmetric
            auto&  ac = upper[u - 1].arch_center;
            double& x = lower[l].location.x;

            double y = ac.y + sqrt(1 - (ac.x - x) * (ac.x - x));

            if (fequal(y, lower[l].location.y)) {
                res.first.push_back(Vertex{lower[l].location, upper[u - 1].arch_center, upper[l - 1].circle_index});
                res.second.push_back(lower[l]);
            } else if (y > lower[u].location.y) {
                if (state == 0) {
                    assert(new_intersection.size() == 1);
                    res.first.push_back(Vertex{new_intersection[0], upper[u - 1].arch_center, upper[u - 1].circle_index});
                    res.second.push_back(Vertex{new_intersection[0], lower[l - 1].arch_center, lower[l - 1].circle_index});

                    state++;
                }
                res.second.push_back(lower[l]);
            } else {
                if (state == 1) {
                    assert(new_intersection.size() == 1);
                    res.first.push_back (Vertex{new_intersection[0], upper[u - 1].arch_center, upper[u - 1].circle_index});
                    res.second.push_back(Vertex{new_intersection[0], lower[l - 1].arch_center, lower[l - 1].circle_index});

                    state++;
                }
            }

            l++;
        }
    }

    return res;
}

void print_vertex(Vertex v, std::string s) {
    printf("%s: %.9f %.9f %.9f %.9f %d\n", s.c_str(), v.location.x, v.location.y, v.arch_center.x, v.arch_center.y,
           v.circle_index);
}

void print_vertex(Vertex v) {
    print_vertex(v, "");
}

