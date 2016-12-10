#include <printf.h>

#include <vector>

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

