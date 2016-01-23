#include "sorting.h"

static void swap(int *base, size_t i, size_t j) {
    int temp = base[i];
    base[i] = base[j];
    base[j] = temp;
}

/**
 * Sort an array using insertion sort.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
void insertion_sort(int *base, size_t n, size_t size, COMPARE_FUNC compare) {
    for (size_t i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && compare(base[j - 1], base[j]) > 0) {
            swap(base, j, j - 1);
            j--;
        }
    }
}
