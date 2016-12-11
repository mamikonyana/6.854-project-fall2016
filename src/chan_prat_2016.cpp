#include "chan_prat_2016.h"
#include "range_tree.h"


RangeTree::RangeTree(std::vector<Point> points) {
    const int N = points.size();
    root = new node;
    root->index = N/2;
    root->left = NULL;
    root->left = NULL;
}




std::vector<int> prat_chan_diameter_2d(std::vector<Point> &points) {
    // TODO: Implement.
    return std::vector<int>(points.size());
}
