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
 * Initialize an integer array with random values.
 *
 */
static void init_int_array_random(int *array, size_t size) {
    for (int i = 0; i < size; ++i) {
        array[i] = rand();
    }
}

int main(void) {
    size_t size = 16384;
    int array[size];
    srand(time(NULL));

    // Test insertion sort
    printf("Testing insertion sort for random array of size %ld\n", size);
    init_int_array_random(array, size);
    clock_t start = clock();
    insertion_sort(array, size, sizeof(int), compare_int);
    clock_t end = clock();
    double total = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Total time: %.3f\n", total);

    // Test bubble sort
    printf("Testing bubble sort for random array of size %ld\n", size);
    init_int_array_random(array, size);
    start = clock();
    insertion_sort(array, size, sizeof(int), compare_int);
    end = clock();
    total = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Total time: %.3f\n", total);

    // Test selection sort
    printf("Testing selection sort for random array of size %ld\n", size);
    init_int_array_random(array, size);
    start = clock();
    selection_sort(array, size, sizeof(int), compare_int);
    end = clock();
    total = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Total time: %.3f\n", total);

    return 0;
}
