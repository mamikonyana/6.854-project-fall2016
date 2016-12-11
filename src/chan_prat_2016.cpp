#include "chan_prat_2016.h"
#include "range_tree.h"




std::vector<int> chan_prat_diameter_2d(std::vector<Point> &points) {
    // TODO: Implement.
    RangeTree rt = RangeTree(points);

    return std::vector<int>(points.size());
}
