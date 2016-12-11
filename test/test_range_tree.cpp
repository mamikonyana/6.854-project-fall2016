#include <assert.h>
#include "../src/range_tree.h"

void test_range_tree_construct() {
    std::vector<Point> points = load_csv_data("data/5-gon-0.9radius.csv");
    RangeTree rt = RangeTree(points); // 0, 1, 2, 3, 4
    assert(rt.is_root() == true);
    assert(rt.getIndex() == 2);
    assert(rt.get_parent() == NULL);
    assert(rt.is_leaf() == false);
    RangeTree *left_tree = rt.left_child(); // 0, 1, 2
    assert(left_tree->is_left_child() == true);
    assert(left_tree->getIndex() == 1);
    assert(left_tree->get_parent()->getIndex() == 2);
    assert(left_tree->is_leaf() == false);
    RangeTree *left_left_tree = left_tree->left_child(); // 0, 1
    assert(left_left_tree->is_left_child() == true);
    assert(left_left_tree->getIndex() == 0);
    assert(left_left_tree->get_parent()->getIndex() == 1);
    assert(left_left_tree->is_leaf() == false);
    RangeTree *left_right_tree = left_tree->right_child(); // 2
    assert(left_right_tree->is_left_child() == false);
    assert(left_right_tree->getIndex() == 2);
    assert(left_right_tree->get_parent()->getIndex() == 1);
    assert(left_right_tree->is_leaf() == true);
    RangeTree *left_left_left_tree = left_left_tree->left_child(); // 0
    assert(left_left_left_tree->is_left_child() == true);
    assert(left_left_left_tree->getIndex() == 0);
    assert(left_left_left_tree->get_parent()->getIndex() == 0);
    assert(left_left_left_tree->is_leaf() == true);
    RangeTree *left_left_right_tree = left_left_tree->right_child(); // 1
    assert(left_left_right_tree->is_left_child() == false);
    assert(left_left_right_tree->getIndex() == 1);
    assert(left_left_right_tree->get_parent()->getIndex() == 0);
    assert(left_left_right_tree->is_leaf() == true);

    RangeTree *right_tree = rt.right_child(); // 3, 4
    assert(right_tree->is_left_child() == false);
    assert(right_tree->getIndex() == 3);
    assert(right_tree->get_parent()->getIndex() == 2);
    assert(right_tree->is_leaf() == false);
    RangeTree *right_left_tree = right_tree->left_child(); // 3
    assert(right_left_tree->is_left_child() == true);
    assert(right_left_tree->getIndex() == 3);
    assert(right_left_tree->get_parent()->getIndex() == 3);
    assert(right_left_tree->is_leaf() == true);
    RangeTree *right_right_tree = right_tree->right_child(); // 4
    assert(right_right_tree->is_left_child() == false);
    assert(right_right_tree->getIndex() == 4);
    assert(right_right_tree->get_parent()->getIndex() == 3);
    assert(right_right_tree->is_leaf() == true);

    printf("PASS: range_tree_construct\n");
}

void test_locate_tree() {
    std::vector<Point> points = load_csv_data("data/5-gon-0.9radius.csv");
    RangeTree rt = RangeTree(points); // 0, 1, 2, 3, 4
    assert(rt.locate_tree(5) == NULL);
    RangeTree *four_tree = rt.locate_tree(4);
    assert(four_tree->getIndex() == 4);
    assert(four_tree->get_parent()->getIndex() == 3);
    RangeTree *three_tree = rt.locate_tree(3);
    assert(three_tree->getIndex() == 3);
    assert(three_tree->get_parent()->getIndex() == 3);
    RangeTree *two_tree = rt.locate_tree(2);
    assert(two_tree->getIndex() == 2);
    assert(two_tree->get_parent()->getIndex() == 1);
    RangeTree *one_tree = rt.locate_tree(1);
    assert(one_tree->getIndex() == 1);
    assert(one_tree->get_parent()->getIndex() == 0);
    RangeTree *zero_tree = rt.locate_tree(0);
    assert(zero_tree->getIndex() == 0);
    assert(zero_tree->get_parent()->getIndex() == 0);
    printf("PASS: locate_tree\n");
}

int main() {
    test_range_tree_construct();
    test_locate_tree();
    return 0;
}
