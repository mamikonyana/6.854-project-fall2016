#include <printf.h>

#include <vector>

#include "naive.h"
#include "helpers.h"

std::vector<int> naive_diameter(std::vector<Point> &points) {
    int size = points.size();
    std::vector<int> j_star(size);
    std::vector<int> k(size); // minimum violator for i'th circle, minus 1
    for (int i = 0; i < size; i++) {
        int j = i + 1;
        for (; j < size && difference_l2norm(points[i], points[j]) < 1.0;
               j++) {}
        k[i] = j - 1;
    }
    for (int i = 0; i < size; i++) {
        j_star[i] = *std::min_element(&k[i], &k[k[i]]);
    }
    return j_star;
}

std::vector<int> naive_monotonicity_2d(std::vector<Point> &points) {
    int size = points.size();
    std::vector<int> answer(size);

    for (int i = 0; i < size; i++) {
        int j = i;
        std::pair<double, double> range;
        for (; j < size - 1; j++) {

            std::pair<double, double> new_range = positive_directions(points[j], points[j + 1]);

            // printf("================= before (%d, %d): %.5f, %.5f\n", i, j, range.first * 180 / PI,
            //        range.second * 180 / PI);
            // printf("=================  new   (%d, %d): %.5f, %.5f\n", i, j, new_range.first * 180 / PI,
            //        new_range.second * 180 / PI);
            if (i == j) {
                range = new_range;
            } else {
                range = range_intersect(range, new_range);
            }

            // printf("=================  after (%d, %d): %.5f, %.5f\n", i, j, range.first * 180 / PI, range.second * 180 / PI);
            if (range.first < 0) {
                break;
            }
        }
        answer[i] = j;
    }
    return answer;
}

