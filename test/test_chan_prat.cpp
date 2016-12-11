#include <assert.h>
#include "../src/chan_prat_2016.h"
#include "../src/range_tree.h"

void test_range_tree_construct() {
    std::vector<Point> points = {{0.0, 1.0},
                                 {0.1, 1.1},
                                 {1.2, 1.2},
                                 {1.3, 1.3},
                                 {1.4, 1.4}};
    RangeTree rt = RangeTree(points); // 0, 1, 2, 3, 4
    assert(rt.getIndex() == 2);
    assert(rt.getParent() == NULL);
    RangeTree *left_tree = rt.leftChild(); // 0, 1, 2
    assert(left_tree->getIndex() == 1);
    assert(left_tree->getParent()->getIndex() == 2);
    RangeTree *left_left_tree = left_tree->leftChild(); // 0, 1
    assert(left_left_tree->getIndex() == 0);
    assert(left_left_tree->getParent()->getIndex() == 1);
    RangeTree *left_left_left_tree = left_left_tree->leftChild(); // 0
    assert(left_left_left_tree->getIndex() == 0);
    assert(left_left_left_tree->getParent()->getIndex() == 0);
    RangeTree *left_left_right_tree = left_left_tree->rightChild(); // 1
    assert(left_left_right_tree->getIndex() == 1);
    assert(left_left_right_tree->getParent()->getIndex() == 0);

    RangeTree *right_tree = rt.rightChild(); // 3, 4
    assert(right_tree->getIndex() == 3);
    assert(right_tree->getParent()->getIndex() == 2);
    RangeTree *right_left_tree = right_tree->leftChild(); // 3
    assert(right_left_tree->getIndex() == 3);
    assert(right_left_tree->getParent()->getIndex() == 3);
    RangeTree *right_right_tree = right_tree->rightChild(); // 4
    assert(right_right_tree->getIndex() == 4);
    assert(right_right_tree->getParent()->getIndex() == 3);

    printf("PASS: range_tree_construct\n");
}

int main() {
    test_range_tree_construct();
    return 0;
}
