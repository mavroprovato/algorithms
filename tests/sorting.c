/**
 * Test program for sorting.
 */
#include "sorting.h"

#include <getopt.h>
#include <sys/time.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * Returns the number of milliseconds since the UNIX epoch.
 *
 * @return The number of milliseconds since the UNIX epoch.
 */
double get_time(void) {
    struct timeval t;
    gettimeofday(&t, NULL);

    return t.tv_sec + t.tv_usec * 1e-6;
}

/**
 * Compares two integer numbers.
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
    for (size_t i = 0; i < size; ++i) {
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
double benchmark_search(SORT_FUNC sort, void *array, size_t n, size_t size, COMPARE_FUNC compare) {
    double start = get_time();
    sort(array, n, size, compare);
    double end = get_time();

    return end - start;
}

int main(int argc, char **argv) {
    static struct option long_options[] = {
        {"algorithm", required_argument, 0, 'a'},
        {"num", required_argument, 0, 'n'},
        {0, 0, 0, 0}
    };
    int option_index = 0;
    int c;
    SORT_FUNC sort = NULL;
    size_t num_elements = 0;
    while ((c = getopt_long(argc, argv, "a:n:", long_options, &option_index)) != -1) {
        switch(c) {
            case 'a':
                if (strcmp(optarg, "insertion") == 0) {
                    sort = insertion_sort;
                } else if (strcmp(optarg, "bubble") == 0) {
                    sort = bubble_sort;
                } else if (strcmp(optarg, "selection") == 0) {
                    sort = selection_sort;
                } else if (strcmp(optarg, "shell") == 0) {
                    sort = shell_sort;
                } else if (strcmp(optarg, "merge") == 0) {
                    sort = merge_sort;
                } else if (strcmp(optarg, "quick") == 0) {
                    sort = quick_sort;
                } else {
                    fprintf(stderr, "Invalid sorting algorithm: %s\n", optarg);
                    return EXIT_FAILURE;
                }
                break;
            case 'n':
                num_elements = (size_t) atoi(optarg);
                if (num_elements < 0) {
                    fprintf(stderr, "The number of elements to sort must be "
                                    "positive.");
                    return EXIT_FAILURE;
                }
                break;
            default:
                printf("c: %c", c);
                continue;
        }
    }

    // Perform sorting and print the running time
    srand(time(NULL));
    void *array = malloc(num_elements * sizeof(int));
    if (!array) {
        fprintf(stderr, "Cannot allocate memory.\n");
        return EXIT_FAILURE;
    }

    init_int_array_random(array, num_elements);
    printf("Testing sort for random array of size %zu\n", num_elements);
    double elapsed = benchmark_search(sort, array, num_elements, sizeof(int), compare_int);
    printf("Total time: %.3f\n", elapsed);

    // Free memory
    free(array);

    return EXIT_SUCCESS;
}
