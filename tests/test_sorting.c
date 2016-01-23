#include <stdio.h>

#include "sorting.h"

static int compare_int(int first, int second) {
    if (first > second) {
        return 1;
    } else if (first < second) {
        return -1;
    } else {
        return 0;
    }
}

int main(void) {
    int test[] = { 54 , 34, 66, 1 , 93, 44};
    insertion_sort(test, 6, sizeof(int), compare_int);

    for (size_t i = 0; i < 6; i++) {
        printf("%d\n", test[i]);
    }

    return 0;
}
