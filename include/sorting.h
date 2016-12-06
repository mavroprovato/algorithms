#ifndef _SORT_H
#define _SORT_H

#include <stdbool.h>
#include <stddef.h>

#include "util.h"

/**
 * Prototype for a function that sorts an array.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
typedef void (*SORT_FUNC) (void *base, size_t n, size_t size, COMPARE_FUNC compare);

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

/**
 * Sort an array using shell sort.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
void shell_sort(void *base, size_t n, size_t size, COMPARE_FUNC compare);

/**
 * Sort an array using merge sort.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
void merge_sort(void *base, size_t n, size_t size, COMPARE_FUNC compare);

/**
 * Sort an array using quick sort.
 *
 * @param base A pointer to the first element of the array to be sorted.
 * @param n The number of elements in the array pointed by base.
 * @param size The size in bytes of each element in the array.
 * @param compare Pointer to a function that compares two elements.
 */
void quick_sort(void *base, size_t n, size_t size, COMPARE_FUNC compare);

#endif // _SORT_H
