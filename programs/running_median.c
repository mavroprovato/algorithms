#include "bheap.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Compares two heap elements. The elements should be integers.
 *
 * @param first Pointer to the first element.
 * @param second Pointer to the second element.
 * @return A negative value if a appears before b in lexicographical order, zero if a and b are equal or a positive
 * value if a appears after b in lexicographical order.
 */
int compare_long(const void *first, const void *second) {
    long ulfirst = *((long *) first);
    long ulsecond = *((long *) second);

    if (ulfirst > ulsecond) {
        return 1;
    } else if (ulfirst < ulsecond) {
        return -1;
    } else {
        return 0;
    }
}

/**
 * Reverse compare of two heap elements. The elements should be integers.
 *
 * @param first Pointer to the first element.
 * @param second Pointer to the second element.
 * @return A negative value if a appears after b in lexicographical order, zero
 * if a and b are equal or a positive value if a appears before b in
 * lexicographical order.
 */
int compare_long_reverse(const void *first, const void *second) {
    long ulfirst = *((long *) first);
    long ulsecond = *((long *) second);

    if (ulfirst > ulsecond) {
        return -1;
    } else if (ulfirst < ulsecond) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char **argv) {
    // Open file if it is provided as an argument, or read from standard input.
    FILE * fp;
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        if (!fp) {
            fprintf(stderr, "Could not open file: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    } else {
        fp = stdin;
    }

    // A max heap for storing values less than the median
    BHeap left;
    if (!bh_init(&left, compare_long_reverse)) {
        fprintf(stderr, "Cannot initialize heap.\n");
        return EXIT_FAILURE;
    }

    // A min heap for storing values less than the median
    BHeap right;
    if (!bh_init(&right, compare_long)) {
        fprintf(stderr, "Cannot initialize heap.\n");
        bh_destroy(&left);
        return EXIT_FAILURE;
    }

    // Read all available integers from the input
    int rc = -1;
    double median = 0.0;

    long *num = malloc(sizeof(long));
    if (!num) {
        fprintf(stderr, "Cannot allocate memory.\n");
        goto cleanup;
    }

    while ((rc = fscanf(fp, "%ld", num)) != -1) {
        if (bh_is_empty(&left)) {
            bh_insert(&left, num);
            median = *num;
        } else {
            // Insert new value to the correct heap
            if (*num < median) {
                bh_insert(&left, num);
                if (bh_size(&left) == bh_size(&right) + 2) {
                    bh_insert(&right, bh_remove_min(&left));
                }
            } else {
                bh_insert(&right, num);
                if (bh_size(&right) == bh_size(&left) + 2) {
                    bh_insert(&left, bh_remove_min(&right));
                }
            }

            // Update the median
            if (bh_size(&left) == bh_size(&right)) {
                median = (*(long *) bh_peek(&left) + *(long *) bh_peek(&right)) / 2.0;
            } else if (bh_size(&left) > bh_size(&right)) {
                median = *(long *) bh_peek(&left);
            } else {
                median = *(long *) bh_peek(&right);
            }
        }
        printf("%.1f\n", median);

        // Allocate memory for the next number to be read
        num = malloc(sizeof(long));
        if (!num) {
            fprintf(stderr, "Cannot allocate memory.\n");
            goto cleanup;
        }
    }

cleanup:
    // Cleanup
    free(num);
    while (!bh_is_empty(&left)) {
        free(bh_remove_min(&left));
    }
    bh_destroy(&left);
    while (!bh_is_empty(&right)) {
        free(bh_remove_min(&right));
    }
    bh_destroy(&right);

    return EXIT_SUCCESS;
}
