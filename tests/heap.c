#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bheap.h"

#define TEST_SIZE 100

/**
 * Compares two heap elements. The elements should be integers.
 *
 * @param first Pointer to the first element.
 * @param second Pointer to the second element.
 * @return A negative value if a appears before b in lexicographical order, zero
 * if a and b are equal or a positive value if a appears after b in
 * lexicographical order.
 */
int compare_int(const void *first, const void *second) {
    int ifirst = (intptr_t) first;
    int isecond = (intptr_t) second;

    if (ifirst > isecond) {
        return 1;
    } else if (ifirst < isecond) {
        return -1;
    } else {
        return 0;
    }
}

int main(void) {
    BHeap heap;
    if (!bh_init(&heap, compare_int)) {
        fprintf(stderr, "Cannot create heap.\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < TEST_SIZE; i++) {
        bh_insert(&heap, (void *) (intptr_t) (rand() % (TEST_SIZE * 10)));
    }

    while (!bh_is_empty(&heap)) {
        int val = (intptr_t) bh_remove_min(&heap);
        printf("Getting min: %d\n", val);
    }

    bh_destroy(&heap);

    return EXIT_SUCCESS;
}
