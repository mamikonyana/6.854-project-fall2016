#ifndef INC_6_854_PROJECT_RANGE_TREE_H
#define INC_6_854_PROJECT_RANGE_TREE_H

#include <vector>
#include "helpers.h"
#include "polyarc.h"

class RangeTree {
public:
    RangeTree(std::vector<Point> points);

    int getIndex();

    RangeTree * locate_tree(int index);

    RangeTree * get_parent();

    RangeTree * left_child();

    RangeTree * right_child();

    bool is_left_child();
    bool is_root();

    bool is_point_outside_intersection(std::vector<double> &vector);

    bool is_leaf();

private:
    RangeTree(std::vector<Point> &points, int first, int last, RangeTree *parent);

    RangeTree *left;
    RangeTree *right;
    RangeTree *parent;
    int index;
    PolyArc polyArc;
};


#endif //INC_6_854_PROJECT_RANGE_TREE_H
