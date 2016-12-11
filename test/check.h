#include <printf.h>

#include <vector>
#include <assert.h>

void assert_equal(double d1, double d2, double prec) {
    if (std::abs(d1 - d2) < prec) {
        return;
    } else {
        printf("Checking %f < %f (with prec %f), which is wrong", d1, d2, prec);
        assert(std::abs(d1 - d2) < prec);
    }
}


void check_vectors(std::vector<int> expected, std::vector<int> received, std::string name) {
    if (expected == received) {
        printf("PASS: %s\n", name.c_str());
    } else {
        printf("FAIL: %s\n", name.c_str());
        printf("<<<< expected");
        for (int i = 0; i < expected.size(); ++i) {
            printf(" %d", expected[i]);
        }
        printf("\n");
        printf(">>>> received");
        for (int i = 0; i < received.size(); ++i) {
            printf(" %d", received[i]);
        }
        printf("\n");
    }
    printf("\n");
}

