#include "range_tree.h"

RangeTree::RangeTree(std::vector<Point> points) : RangeTree(points, 0, points.size() - 1, NULL) {}


RangeTree::RangeTree(std::vector<Point> &points, int first, int last, RangeTree *parent) {
    this->parent = parent;
    int mid = (first + last) / 2;
    index = mid;
    if (first == last) {
        this->left = NULL;
        this->right= NULL;
        polyArc = PolyArc(Point2D{points[index][0], points[index][1]});
        return;
    }
    this->left = new RangeTree(points, first, mid, this);
    this->right = new RangeTree(points, mid + 1, last, this);
    polyArc = left->polyArc.intersect(right->polyArc);
}

int RangeTree::getIndex() {
    return index;
}

RangeTree *RangeTree::get_parent() {
    return this->parent;
}

RangeTree *RangeTree::left_child() {
    return this->left;
}

RangeTree *RangeTree::right_child() {
    return this->right;
}

RangeTree *RangeTree::locate_tree(int query_index) {
    if (this->left == NULL && this->right == NULL) {
        if (index == query_index) {
            return this;
        } else {
            return NULL;
        }
    }
    if (query_index > index) {
        return this->right->locate_tree(query_index);
    } else {
        return this->left->locate_tree(query_index);
    }
}

bool RangeTree::is_left_child() {
    return this->parent != NULL && this->parent->left == this;
}

bool RangeTree::is_root() {
    return this->parent == NULL;
}

bool RangeTree::is_point_outside_intersection(Point &vector) {
    return !polyArc.contains(Point2D{vector[0], vector[1]});
}

bool RangeTree::is_leaf() {
    // nodes only have 0 or 2 children.
    return this->left == NULL;
}

