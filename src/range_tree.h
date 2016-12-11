#ifndef INC_6_854_PROJECT_RANGE_TREE_H
#define INC_6_854_PROJECT_RANGE_TREE_H

#include <vector>
#include "helpers.h"

struct node {
    node() {}

    int index;
    node *left;
    node *right;
    node *parent;
};

class RangeTree {
public:
    RangeTree(std::vector<Point> points);

    int getIndex();

    RangeTree * getParent();

    RangeTree * leftChild();

    RangeTree * rightChild();

private:
    RangeTree(std::vector<Point> &points, int first, int last, RangeTree *parent);

    RangeTree *left;
    RangeTree *right;
    RangeTree *parent;
    int index;
};


#endif //INC_6_854_PROJECT_RANGE_TREE_H
