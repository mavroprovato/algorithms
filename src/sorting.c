#include "sorting.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

/**
 * Swap the two elements.
 *
 * @param a Pointer of the secondelement to swap
 * @param b Pointer of the second element to swap
 * @param size The size in bytes of each element to be swapped.
 */
static void swap(void *a, void *b, size_t size) {
    size_t k = size;
    while (k-- > 0) {
        char temp = *((char *) a + k);
        *((char *) a + k) = *((char *) b + k);
        *((char *) b + k) = temp;
    }
}

/**
 * Check if the provided array is sorted.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
bool sorted(void *base, size_t n, size_t size, COMPARE_FUNC compare) {
    for (size_t i = 0; i < n - 1; i++) {
        if (compare(base + i * size, base + (i + 1) * size) > 0) {
            return false;
        }
    }

    return true;
}

/**
 * Sort an array using insertion sort.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
void insertion_sort(void *base, size_t n, size_t size, COMPARE_FUNC compare) {
    for (size_t i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && compare(base + (j - 1) * size, base + j * size) > 0) {
            swap(base + (j - 1) * size, base + j * size, size);
            j--;
        }
        // Invariant: The elements up until i must be sorted.
        assert(sorted(base, i, size, compare));
    }
    // Assertion: The array must be sorted.
    assert(sorted(base, n, size, compare));
}

/**
 * Sort an array using bubble sort.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
void bubble_sort(void *base, size_t n, size_t size, COMPARE_FUNC compare) {
    for (size_t i = 1; i < n; i++) {
        bool swapped = false;
        for (size_t j = n - 1; j >= i; j--) {
            if (compare(base + (j - 1) * size, base + j * size) > 0) {
                swap(base + (j - 1) * size, base + j * size, size);
                swapped = true;
            }
        }

        // Invariant: The elements up until i must be sorted.
        assert(sorted(base, i, size, compare));
        if (!swapped) {
            break;
        }
    }
    // Assertion: The array must be sorted.
    assert(sorted(base, n, size, compare));
}

/**
 * Sort an array using selection sort.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
void selection_sort(void *base, size_t n, size_t size, COMPARE_FUNC compare) {
    for (size_t i = 0; i < n; i++) {
        int min = i;
        for (size_t j = i + 1; j < n; j++) {
            if (compare(base + j * size, base + min * size) < 0) {
                min = j;
            }
        }
        swap(base + i * size, base + min * size, size);

        // Invariant: The elements up until i + 1 must be sorted.
        assert(sorted(base, i + 1, size, compare));
    }
    // Assertion: The array must be sorted.
    assert(sorted(base, n, size, compare));
}
