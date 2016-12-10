#include "helpers.h"
#include <math.h>
#include <stdlib.h>

double difference_l2norm(Point a, Point b) {
    double norm = 0.0;
    for (int i = 0; i < a.size(); i++) {
        norm += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sqrt(norm);
}

std::vector<Point> load_csv_data(std::string path) {
    const char DELIMITER[2] = ",";

    FILE *stream = fopen(path.c_str(), "r");
    char line[1024];
    char *token;

    std::vector<Point> points(0);

    int num_columns = 0;

    // Consume header and calculate number of columns
    fgets(line, 1024, stream);
    token = strtok(line, DELIMITER);
    if (token == NULL) {
        num_columns = 1;
    }
    // Walk through other tokens
    while (token != NULL) {
        token = strtok(NULL, DELIMITER);
        num_columns += 1;
    }

    while (fgets(line, 1024, stream)) {
        Point p(num_columns);
        token = strtok(line, DELIMITER);
        p[0] = atof(token);
        for (int i = 1; i < num_columns; i++) {
            token = strtok(NULL, DELIMITER);
            p[i] = atof(token);
        }
        points.push_back(p);
    }
    return points;
}


double standard_angle(double angle) {
    double multiple = angle / (2 * PI);
    double fraction = multiple - ((long) multiple);
    if (fraction < 0) {
        fraction = 1 + fraction;
    }
    return 2 * PI * fraction;
}

double relative_angle(Point &start, Point& end) {
    double dx = end[0] - start[0];
    double dy = end[1] - start[1];
    if (dx == 0) {
        if (dy > 0) {
            return PI / 2;
        } else if (dy < 0) {
            return -PI / 2;
        } else {
            return 0.0; // TODO: return something more informative. 10? :)
        }
    }
    double a = atan(dy / dx);
    if (dx > 0) {
        return standard_angle(a);
    } else {
        return standard_angle(a + PI);
    }
}

double max(double a, double b) {
    if (a > b) {
        return a;
    }
    return b;
}

double min(double a, double b) {
    if (a < b) {
        return a;
    }
    return b;
}

std::pair<double, double> positive_directions(Point &p1, Point &p2) {
    double direction = relative_angle(p1, p2);
    double range_begin = standard_angle(direction - PI / 2);
    double range_end = standard_angle(direction + PI / 2);

    return std::make_pair(range_begin, range_end);
}

std::pair<double, double> positive_directions(Point &p1, Point &p2, std::pair<double, double> range) {
    double direction = relative_angle(p1, p2);
    double range_begin = standard_angle(direction - PI / 2);
    double range_end = standard_angle(direction + PI / 2);

    if (range_begin > range_end) {
        range_end += 2 * PI;
    }
    double before_begin = range.first;
    double before_end = range.second;
    if (before_begin > before_end) {
        before_end += 2 * PI;
    }
    double new_start = max(range_begin, before_begin);
    double new_end = min(range_end, before_end);
    if (new_start > new_end) {
        return std::make_pair(-1.0, -1.0); // TODO: Better approach for reporting infeasible.
    }
    return std::make_pair(standard_angle(new_start), standard_angle(new_end));
}

