#ifndef INC_6_854_PROJECT_HELPERS_H
#define INC_6_854_PROJECT_HELPERS_H

#include <vector>

#define PI 3.14159265

typedef Point std::vector< double >;

double l2norm(Point a, Point b);

std::vector< Point > loadData(std::string path);

double angle(Point vector);

std::pair< double, double > positive_directions(Point vector, std::pair< double, double > overlap);

#endif // INC_6_854_PROJECT_HELPERS_H

