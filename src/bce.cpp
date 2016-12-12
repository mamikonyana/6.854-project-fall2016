#include "bce.h"
#include "helpers.h"

std::vector<int> bce_monotonicity_2d(std::vector<Point> &points) {
    int n = points.size();
    std::vector<int> answer(n);

    std::vector<std::pair<double, double> > back_ranges(n);

    int prev = 0, curr = 0;
    while (curr < n - 1) {
        // printf("anchor: %d\n", curr);
        back_ranges[curr] = std::make_pair(-1, -1);
        for (int i = curr - 1; i >= prev; --i) {
            auto new_range = positive_directions(points[i + 1], points[i]);
            // printf("new range %d: %.2f %.2f\n", i, new_range.first, new_range.second);
            if (i == curr - 1) {
                back_ranges[i] = new_range;
            } else {
                back_ranges[i] = range_intersect(back_ranges[i + 1], new_range);
            }
            // printf("back ranges %d: %.2f %.2f\n", i, back_ranges[i].first, back_ranges[i].second);
        }

        // printf("%d %d\n", prev, curr);
        for (int i = prev; i < curr; i++) {
            // printf("%.2f %.2f\n", back_ranges[i].first, back_ranges[i].second);
        }

        int next;
        std::pair<double, double> range;
        for (next = curr; next < n - 1; ++next) {
            auto new_range = positive_directions(points[next], points[next + 1]);
            // printf("new range %d: %.2f %.2f\n", next, new_range.first, new_range.second);
            if (next == curr) {
                range = new_range;
            } else {
                range = range_intersect(range, new_range);
            }
            printf("BCE=== start %d, after %d: %.2f %.2f\n", curr, next, range.first * 180 / PI,
                   range.second * 180 / PI);

            while (prev < curr) {
                auto rev_range = back_ranges[prev];
                rev_range.first += PI;
                rev_range.second += PI;
                rev_range.first = standard_angle(rev_range.first);
                rev_range.second = standard_angle(rev_range.second);

                // printf("prev: %d; curr: %d; next: %d; rev_range: %.2f, %.2f; range: %.2f, %.2f; intersect: %.2f, %.2f\n", prev, curr, next, rev_range.first, rev_range.second, range.first, range.second, range_intersect(rev_range, range).first, range_intersect(rev_range, range).second);

                if (range_intersect(rev_range, range).first >= 0) {
                    break;
                }
                answer[prev] = next;
                printf("answer[%d] = %d\n", prev, answer[prev]);
                prev += 1;
            }

            if (range.first < 0) {
                break;
            }
        }

        curr = next;
    }
    while (prev < n) {
        answer[prev] = n - 1;
        printf("answer[%d] = %d\n", prev, answer[prev]);
        prev += 1;
    }

    // printf("anchor: %d\n", curr);
    return answer;
}

std::vector<int> bce_diameter_2d(std::vector<Point> &points) {
    std::vector<int> answer(points.size());
    return answer;
}

