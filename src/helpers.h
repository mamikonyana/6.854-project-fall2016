#ifndef INC_6_854_PROJECT_HELPERS_H
#define INC_6_854_PROJECT_HELPERS_H

#include <vector>
#include <utility>
#include <string>

#define PI 3.14159265

typedef std::vector<double> Point;

double difference_l2norm(Point a, Point b);

std::vector <Point> load_csv_data(std::string path);

double angle(Point& p1, Point& p2);

std::pair< double, double > positive_directions(Point& p1, Point& p2);

std::pair< double, double > positive_directions(Point& p1, Point& p2, std::pair< double, double > range);

#endif // INC_6_854_PROJECT_HELPERS_H

