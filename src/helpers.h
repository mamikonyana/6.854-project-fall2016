#ifndef INC_6_854_PROJECT_HELPERS_H
#define INC_6_854_PROJECT_HELPERS_H

#include <vector>
#include <utility>
#include <string>

#define PI 3.14159265

typedef std::vector<double> Point;

double difference_l2norm(Point a, Point b);

std::vector <Point> load_csv_data(std::string path);
//
double angle(Point& vector);

std::pair< double, double > positive_directions(Point& vector);

std::pair< double, double > positive_directions(Point& vector, std::pair< double, double > overlap);

#endif // INC_6_854_PROJECT_HELPERS_H

