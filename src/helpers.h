#ifndef INC_6_854_PROJECT_HELPERS_H
#define INC_6_854_PROJECT_HELPERS_H

#include <vector>
#include <utility>
#include <string>

#define PI 3.14159265

typedef std::vector<double> Position;

double difference_l2norm(Position a, Position b);

std::vector <Position> load_csv_data(std::string path);
//
double angle(Position& vector);

std::pair< double, double > positive_directions(Position& vector);

std::pair< double, double > positive_directions(Position& vector, std::pair< double, double > overlap);

#endif // INC_6_854_PROJECT_HELPERS_H

