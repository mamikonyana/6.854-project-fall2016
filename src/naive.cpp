#include <printf.h>

#include <vector>

#include "naive.h"
#include "helpers.h"

std::vector< int > naive_diameter(std::vector< Point >& points) {
    int size = points.size();
    std::vector< int > answer(size);
    for (int i = 0; i < size; i++) {
        int j = i + 1;
        for (; j < size && difference_l2norm(points[i], points[j]) < 1.0;
               j++) {}
        answer[i] = j - 1;
    }
    return answer;
}

std::vector< int > naive_monotonicity_2d(std::vector< Point >& points) {
    int size = points.size();
    std::vector< int > answer(size);

    for (int i = 0; i < size; i++) {
        int j = i;
        for (; j < size - 1; j++) {
            std::pair< double, double > range;

            if (i == j) {
                range = positive_directions(points[j], points[j + 1]);
            } else {
                range = positive_directions(points[j], points[j + 1], range);
            }
            printf(" ================ i: %d, j: %d, angles: %.1f, %1f \n", i, j, range.first * 180 / PI, range.second * 180 / PI);
            if (range.first < 0) {
                break;
            }
        }
        answer[i] = j;
    }
    return answer;
}

