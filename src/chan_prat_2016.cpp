#include "chan_prat_2016.h"
#include "range_tree.h"


std::vector<int> chan_prat_diameter_2d(std::vector<Point> &points) {
    RangeTree rt = RangeTree(points);

    unsigned long N = points.size();
    std::vector<int> answer = std::vector<int>(N);
    RangeTree *node;
    for (int i = 0; i < N; i++) {
        node = rt.locate_tree(i);
        // printf("start == %d ", node->getIndex());
        bool going_up = true;
        // Up phase
        while (going_up && node->is_root() == false) {
            bool from_left = node->is_left_child();
            node = node->get_parent();
            if (from_left) {
                bool found_far_point = node->right_child()->is_point_outside_intersection(points[i]);
                if (found_far_point) {
                    going_up = false;
                    break;
                }
            }
        }
        if (going_up) {
            answer[i] = N - 1;
            continue;
        }
        node = node->right_child();
        while (!going_up) {
            if (node->is_leaf()) {
                // We care about the largest that is not far, not smallest that is far.
                answer[i] = node->getIndex() - 1;
                break;
            }
            bool found_far_point = node->left_child()->is_point_outside_intersection(points[i]);
            if (found_far_point) {
                node = node->left_child();
            } else {
                node = node->right_child();
            }
        }
    }
    for (int i = N - 2; i >= 0; i--) {
        // printf("%d, answer = %d, right_answer = %d\n", i, answer[i], answer[i+1]);
        answer[i] = std::min(answer[i+1], answer[i]);
    }
    return answer;
}
