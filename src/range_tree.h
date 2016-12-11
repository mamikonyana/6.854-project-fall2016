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

    RangeTree * getParent();

    RangeTree * leftChild();

    RangeTree * rightChild();

private:
    RangeTree(std::vector<Point> &points, int first, int last, RangeTree *parent);

    RangeTree *left;
    RangeTree *right;
    RangeTree *parent;
    int index;
    PolyArc polyArc;
};


#endif //INC_6_854_PROJECT_RANGE_TREE_H
