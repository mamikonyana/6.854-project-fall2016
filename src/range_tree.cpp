#include "range_tree.h"

RangeTree::RangeTree(std::vector<Point> points) : RangeTree(points, 0, points.size() - 1, NULL) {}


RangeTree::RangeTree(std::vector<Point> &points, int first, int last, RangeTree *parent) {
    this->parent = parent;
    int mid = (first + last) / 2;
    index = mid;
    if (first == last) {
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

RangeTree *RangeTree::getParent() {
    return this->parent;
}

RangeTree *RangeTree::leftChild() {
    return this->left;
}

RangeTree *RangeTree::rightChild() {
    return this->right;
}

