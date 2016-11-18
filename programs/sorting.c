#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <argtable2.h>

#include "sorting.h"

/** The program name. */
const char *prog_name = "sort";

/**
 * Returns the number of milliseconds since the Epoch.
 *
 * @return The number of milliseconds since the Epoch.
 */
double get_time(void) {
    struct timeval t;
    gettimeofday(&t, NULL);

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
double benchmark_search(SORT_FUNC sort, void *array, size_t n, size_t size,
                        COMPARE_FUNC compare) {
    double start = get_time();
    sort(array, n, size, compare);
    double end = get_time();

    return end - start;
}

int main(int argc, char **argv) {
    // The argument list specification
    struct arg_str *algo = arg_str1("a", "algorithm", "<algorithm>",
        "The sorting algorithm to use.");
    struct arg_rem *algo2  = arg_rem(NULL, "Must be one of 'insertion', "
        "'bubble', 'selection', 'shell', 'merge' or 'quick'");
    struct arg_int *num = arg_int1("n","num", "<n>",
        "The number of elements to sort");
    struct arg_lit *help = arg_lit0("h", "help",
        "Print this help message and exit");
    struct arg_end *end = arg_end(20);
    void *arg_table[] = { algo, algo2, num, help, end };

    // Verify the arg_table[] entries were allocated sucessfully
    if (arg_nullcheck(arg_table) != 0) {
        printf("%s: insufficient memory\n", prog_name);
        return 1;
    }

    // Parse the arguments
    int num_errors = arg_parse(argc, argv, arg_table);

    // Display help if requested
    if (help->count > 0) {
        printf("Usage: %s", prog_name);
        arg_print_syntax(stdout, arg_table, "\n");
        printf("Sort elements from standard input using various sorting "
               "algorithms.\n\n");
        arg_print_glossary(stdout, arg_table,"  %-25s %s\n");
        return 0;
    }

    // Check for errors
    if (num_errors > 0) {
        arg_print_errors(stdout, end, prog_name);
        printf("Try '%s --help' for more information.\n", prog_name);
        return 1;
    }

    // Get the sorting algorithm
    SORT_FUNC sort;
    if (strcmp(*algo->sval, "insertion") == 0) {
        sort = insertion_sort;
    } else if (strcmp(*algo->sval, "bubble") == 0) {
        sort = bubble_sort;
    } else if (strcmp(*algo->sval, "selection") == 0) {
        sort = selection_sort;
    } else if (strcmp(*algo->sval, "shell") == 0) {
        sort = shell_sort;
    } else if (strcmp(*algo->sval, "merge") == 0) {
        sort = merge_sort;
    } else if (strcmp(*algo->sval, "quick") == 0) {
        sort = quick_sort;
    } else {
        printf("Invalid sorting algorithm: %s\n", *algo->sval);
        return 1;
    }

    // Check the number of elements
    if (*num->ival < 0) {
        printf("The number of elements to sort must be positive.");
        return 1;
    }

    // Perform sorting and print the running time
    srand(time(NULL));
    void *array = malloc(*num->ival * sizeof(int));
    init_int_array_random(array, *num->ival);
    printf("Testing %s sort for random array of size %d\n", *algo->sval,
        *num->ival);
    double elapsed = benchmark_search(sort, array, *num->ival, sizeof(int),
        compare_int);
    printf("Total time: %.3f\n", elapsed);

    // Free memory
    free(array);
    arg_freetable(arg_table, sizeof(arg_table) / sizeof(arg_table[0]));

    return 0;
}
