#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorting.h"

/**
 * Compares two integer numbers
 *
 * @param first The first integer.
 * @param second The second integer.
 * @return 1 if the first integer is greather that the second, -1 if the first
 * is less than the second, and 0 if they are equal.
 */
static int compare_int(const void *first, const void *second) {
    int ifirst = *((int *) first);
    int isecond = *((int *) second);
    if (ifirst > isecond) {
        return 1;
    } else if (ifirst < isecond) {
        return -1;
    } else {
        return 0;
    }
}

/**
 * Initialize array with random values.
 */
static void init_int_array_random(int *array, size_t size) {
    for (int i = 0; i < size; ++i) {
        array[i] = rand();
    }
}

int main(void) {
    size_t sizes[8] = {
        256, 512, 1024, 2048, 4096, 8192, 16384, 32768
    };
    srand(time(NULL));

    for (int i = 0; i < 8; i++) {
        printf("Testing insertion sort for random array of size %ld\n",
               sizes[i]);
        int array[sizes[i]];
        init_int_array_random(array, sizes[i]);
        clock_t start = clock();
        bubble_sort(array, sizes[i], sizeof(int), compare_int);
        clock_t end = clock();
        double total = (double) (end - start) / CLOCKS_PER_SEC;
        printf("Total time taken by CPU: %.3f\n", total);
    }

    return 0;
}
