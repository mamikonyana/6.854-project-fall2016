#ifndef INC_6_854_PROJECT_HELPERS_H
#define INC_6_854_PROJECT_HELPERS_H

#include <vector>
#include <utility>
#include <string>
#include <cmath>

const double PI  = 2 * acos(0.0);
const double EPS = 1e-9;

typedef std::vector<double> Point;

bool fequal(double a, double b);

double difference_l2norm(Point a, Point b);

std::vector <Point> load_csv_data(std::string path);

double standard_angle(double angle);

double relative_angle(Point& p1, Point& p2);

std::pair<double, double> range_intersect(std::pair< double, double > r1, std::pair< double, double > r2);

std::pair< double, double > positive_directions(Point& p1, Point& p2);

std::pair< double, double > positive_directions(Point& p1, Point& p2, std::pair< double, double > range);

#endif // INC_6_854_PROJECT_HELPERS_H

