#ifndef INC_6_854_PROJECT_HELPERS_H
#define INC_6_854_PROJECT_HELPERS_H

#include <vector>
#include <utility>

#define PI 3.14159265

typedef std::vector<double> Position;

double difference_l2norm(Position a, Position b);

// std::vector< Point > loadData(std::string path);
//
// double angle(Point vector);

std::pair< double, double > positive_directions(Point vector, std::pair< double, double > overlap);

#endif // INC_6_854_PROJECT_HELPERS_H
