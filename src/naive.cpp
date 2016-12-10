#include <printf.h>

#include <vector>

#include "naive.h"
#include "helpers.h"

std::vector< int > naive_diameter_2d(std::vector< Position >& points) {
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

std::vector< int > naive_monotonicity_2d(std::vector< Position >& points) {
    int size = points.size();
    std::vector< int > answer(size);

    for (int i = 0; i < size; i++) {
        int j = i;
        for (; j < size - 1; j++) {
            std::pair< double, double > range;

            if (i == j) {
                range = positive_directions(points[j]);
            } else {
                range = positive_directions(points[j], range);
            }
            // printf(" ================ i: %d, j: %d, angles: %.1f, %1f \n", i, j, range[0] * 180 / PI, range[1] * 180 / PI);
            if (range.first < 0) {
                break;
            }
        }
        answer[i] = j;
    }
    return answer;
}

