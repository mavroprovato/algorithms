#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorting.h"

#include <sys/time.h>
#include <sys/resource.h>

/**
 * Returns the number of milliseconds since the Epoch.
 *
 * @return The number of milliseconds since the Epoch.
 */
double get_time() {
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);

    return t.tv_sec + t.tv_usec * 1e-6;
}

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
 * @param array The array to initialize.
 * @param size The size of the array.
 */
static void init_int_array_random(int *array, size_t size) {
    for (int i = 0; i < size; ++i) {
        array[i] = rand();
    }
}

/**
 * Benchmarks a sort function.
 *
 * @param sort The sort function to benchmark.
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 * @return The number of milliseconds that sorting took.
 */
double benchmark_search(SORT_FUNC sort, void *array, size_t n, size_t size,
                        COMPARE_FUNC compare) {
    double start = get_time();
    sort(array, n, size, compare);
    double end = get_time();

    return end - start;
}

int main(void) {
    size_t size = 16384;
    int array[size];
    srand(time(NULL));
    double elapsed = 0.0;

    // Test insertion sort
    printf("Testing insertion sort for random array of size %ld\n", size);
    init_int_array_random(array, size);
    elapsed = benchmark_search(insertion_sort, array, size, sizeof(int),
                               compare_int);
    printf("Total time: %.3f\n", elapsed);

    // Test bubble sort
    printf("Testing bubble sort for random array of size %ld\n", size);
    init_int_array_random(array, size);
    elapsed = benchmark_search(bubble_sort, array, size, sizeof(int),
                               compare_int);
    printf("Total time: %.3f\n", elapsed);

    // Test selection sort
    printf("Testing selection sort for random array of size %ld\n", size);
    init_int_array_random(array, size);
    elapsed = benchmark_search(selection_sort, array, size, sizeof(int),
                               compare_int);
    printf("Total time: %.3f\n", elapsed);

    // Test shell sort
    printf("Testing shell sort for random array of size %ld\n", size);
    init_int_array_random(array, size);
    elapsed = benchmark_search(shell_sort, array, size, sizeof(int),
                               compare_int);
    printf("Total time: %.3f\n", elapsed);

    return 0;
}
