#include "sorting.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The cutoff-threshold to insertion sort
#define CUTOFF 8

/**
 * Swap the two elements.
 *
 * @param a Pointer to the first element to swap.
 * @param b Pointer to the second element to swap.
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
 * Set the value of the first element to the value of the second element.
 *
 * @param a Pointer to the first element.
 * @param b Pointer to the second element.
 * @param size The size in bytes of each element to be swapped.
 */
static void set(void *a, void *b, size_t size) {
    size_t k = size;
    while (k-- > 0) {
        *((char *) a + k) = *((char *) b + k);
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
    if (n < 2) {
        return true;
    }
    for (size_t i = 0; i < n - 1; i++) {
        if (compare(base + i * size, base + (i + 1) * size) > 0) {
            return false;
        }
    }

    return true;
}

/**
 * Check if the provided array is h-sorted.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
bool hsorted(void *base, size_t n, size_t h, size_t size, COMPARE_FUNC compare) {
    for (size_t i = h; i < n - 1; i++) {
        if (compare(base + i * size, base + (i - h) * size) < 0) {
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
    char key[size];
    for (size_t i = 1; i < n; i++) {
        set(key, base + i * size, size);
        int j = i - 1;
        while (j >= 0 && compare(base + j * size, key) > 0) {
            set(base + (j + 1) * size, base + j * size, size);
            j--;
        }
        set(base + (j + 1) * size, key, size);

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

/**
 * Sort an array using shell sort.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
void shell_sort(void *base, size_t n, size_t size, COMPARE_FUNC compare) {
    size_t h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (size_t i = h; i < n; i++) {
            for (size_t j = i;
                 j >= h && compare(base + j * size, base + (j - h) * size) < 0;
                 j -= h) {
                swap(base + j * size, base + (j - h) * size, size);
            }
        }
        // Assertion: The array must be h-sorted.
        assert(hsorted(base, n, h, size, compare));
        h = h / 3;
    }
    // Assertion: The array must be sorted.
    assert(sorted(base, n, size, compare));
}

/**
 * Merge the two sorted subarrays from low to mid and from mid + 1 to high,
 * to one sorted array.
 *
 * @param base The array to be sorted.
 * @param aux The auxiliary array.
 * @param low The index of the first array element to merge.
 * @param mid The index of the element that splits the sorted halves.
 * @param high
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
static void merge(void *base, void *aux, size_t low, size_t mid, size_t high,
                  size_t size, COMPARE_FUNC compare) {
    // Assertion: The array from low to mid must be sorted
    assert(sorted(base + low * size, mid - low, size, compare));
    // Assertion: The array from mid + 1 to high must be sorted
    assert(sorted(base + (mid + 1) * size, high - mid, size, compare));
    // Copy to the auxiliary array
    memcpy(aux + low * size, base + low * size, (high - low + 1) * size);
    // Merge the two halves
    size_t i = low;
    size_t j = mid + 1;
    for (size_t k = low; k <= high; k++) {
        if (i > mid) {
            // The left half is exausted, take from the right half.
            set(base + size * k, aux + size * j++, size);
        } else if (j > high) {
            // The right half is exausted, take from the left half.
            set(base + size * k, aux + size * i++, size);
        } else if (compare(aux + j * size, aux + i * size) < 0) {
            // The element from the right part is smaller
            set(base + size * k, aux + size * j++, size);
        } else {
            // The element from the left part is smaller
            set(base + size * k, aux + size * i++, size);
        }
    }
}

/**
 * Implement the merge sort on the array, using the auxiliary array for storage.
 *
 * @param base The array to be sorted.
 * @param aux The auxiliary array.
 * @param low The index of the first array element to sort.
 * @param high The index of the last array element to sort.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
static void merge_sort_impl(void *base, void *aux, size_t low, size_t high,
                            size_t size, COMPARE_FUNC compare) {
    // For small arrays, cutoff to insertion sort
    if (high < low + CUTOFF) {
        insertion_sort(base + low * size, high - low + 1, size, compare);
        return;
    }
    // Find the mid point
    size_t mid = low + (high - low) / 2;
    // Sort the two halves
    merge_sort_impl(base, aux, low, mid, size, compare);
    merge_sort_impl(base, aux, mid + 1, high, size, compare);
    // Check if the two subarrays are already sorted, so that we don't need to
    // merge
    if (compare(base + (mid + 1) * size, base + mid * size) > 0) {
        return;
    }
    // Merge the sorted halves
    merge(base, aux, low, mid, high, size, compare);
}

/**
 * Sort an array using merge sort.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
void merge_sort(void *base, size_t n, size_t size, COMPARE_FUNC compare) {
    // Allocate the auxiliary array.
    void *aux = malloc(n * size);
    // Sort the array
    merge_sort_impl(base, aux, 0, n - 1, size, compare);
    // Deallocate the auxiliary array.
    free(aux);
    // Assertion: The array must be sorted.
    assert(sorted(base, n, size, compare));
}
