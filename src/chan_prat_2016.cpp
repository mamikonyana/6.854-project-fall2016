#include "chan_prat_2016.h"
#include "range_tree.h"


std::vector<int> chan_prat_diameter_2d(std::vector<Point> &points) {
    // TODO: Implement.
    RangeTree rt = RangeTree(points);

    std::vector<int> answer = std::vector<int>(points.size());
    RangeTree* leaf;
    for (int i = 0; i < points.size(); i++) {
        leaf = rt.locate_tree(i);
        printf("%d\n", leaf->getIndex());
    }
    return answer;
}
