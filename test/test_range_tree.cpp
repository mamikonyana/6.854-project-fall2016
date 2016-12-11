#include <assert.h>
#include "../src/range_tree.h"

void test_range_tree_construct() {
    std::vector<Point> points = load_csv_data("data/5-gon-0.9radius.csv");
    RangeTree rt = RangeTree(points); // 0, 1, 2, 3, 4
    assert(rt.getIndex() == 2);
    assert(rt.getParent() == NULL);
    RangeTree *left_tree = rt.leftChild(); // 0, 1, 2
    assert(left_tree->getIndex() == 1);
    assert(left_tree->getParent()->getIndex() == 2);
    RangeTree *left_left_tree = left_tree->leftChild(); // 0, 1
    assert(left_left_tree->getIndex() == 0);
    assert(left_left_tree->getParent()->getIndex() == 1);
    RangeTree *left_right_tree = left_tree->rightChild(); // 2
    assert(left_right_tree->getIndex() == 2);
    assert(left_right_tree->getParent()->getIndex() == 1);
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

void test_locate_tree() {
    std::vector<Point> points = load_csv_data("data/5-gon-0.9radius.csv");
    RangeTree rt = RangeTree(points); // 0, 1, 2, 3, 4
    assert(rt.locate_tree(5) == NULL);
    RangeTree *four_tree = rt.locate_tree(4);
    assert(four_tree->getIndex() == 4);
    assert(four_tree->getParent()->getIndex() == 3);
    RangeTree *three_tree = rt.locate_tree(3);
    assert(three_tree->getIndex() == 3);
    assert(three_tree->getParent()->getIndex() == 3);
    RangeTree *two_tree = rt.locate_tree(2);
    assert(two_tree->getIndex() == 2);
    assert(two_tree->getParent()->getIndex() == 1);
    RangeTree *one_tree = rt.locate_tree(1);
    assert(one_tree->getIndex() == 1);
    assert(one_tree->getParent()->getIndex() == 0);
    RangeTree *zero_tree = rt.locate_tree(0);
    assert(zero_tree->getIndex() == 0);
    assert(zero_tree->getParent()->getIndex() == 0);
    printf("PASS: locate_tree\n");
}

int main() {
    test_range_tree_construct();
    test_locate_tree();
    return 0;
}
