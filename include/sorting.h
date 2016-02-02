#ifndef _SORT_H
#define _SORT_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Prototype for a function that compares two elements.
 *
 * @param first The first element.
 * @param second The second element.
 * @return A positive integer if the first element is greather that the second,
 * a negetive integer if the first element is less than the second, or zero if
 * they are equal.
 */
typedef int (*COMPARE_FUNC) (const void *first, const void *second);

/**
 * Sort an array using insertion sort.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
void insertion_sort(void *base, size_t n, size_t size, COMPARE_FUNC compare);

/**
 * Sort an array using bubble sort.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
void bubble_sort(void *base, size_t n, size_t size, COMPARE_FUNC compare);

/**
 * Sort an array using selection sort.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
void selection_sort(void *base, size_t n, size_t size, COMPARE_FUNC compare);

#endif // _SORT_H
