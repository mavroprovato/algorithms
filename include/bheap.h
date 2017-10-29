#ifndef _B_HEAP_H
#define _B_HEAP_H

#include "common.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * A binary heap data structure.
 */
typedef struct {
    /** The heap items. */
    void **items;
    /** The heap capacity. */
    size_t capacity;
    /** The heap size. */
    size_t size;
    /** The comparison function. */
    COMPARE_FUNC compare;
} BHeap;

/**
 * Initialize the binary heap data structure.
 *
 * @param bh Pointer to the binary heap data structure.
 * @param compare_func Function used to compare the items.
 * @return true if the data structure was initialized successfully, false otherwise.
 */
bool bh_init(BHeap *bh, COMPARE_FUNC compare_func);

/**
 * Frees resources associated with the binary heap data structure.
 *
 * @param bh Pointer to the binary heap data structure to be freed.
 */
void bh_destroy(BHeap *bh);

/**
 * Check if the binary heap contains any elements.
 *
 * @param bh Pointer to the binary heap data structure.
 * @return true if the heap contains elements, false otherwise.
 */
bool bh_is_empty(BHeap *bh);

/**
 * Return the size of the binary heap.
 *
 * @param bh Pointer to the binary heap data structure.
 * @return The size of the binary heap.
 */
size_t bh_size(BHeap *bh);

/**
 * Insert an element to the heap. Note that NULL elements cannot be inserted in the heap.
 *
 * @param bh Pointer to the binary heap data structure.
 * @param item Pointer to the item to be inserted to the heap.
 * @return true if the element was added successfully, false otherwise.
 */
bool bh_insert(BHeap *bh, void *item);

/**
 * Remove and return the minimum element from the heap.
 *
 * @param bh Pointer to the binary heap data structure.
 * @return The minimum element contained in the heap, or NULL if the heap is empty.
 */
void *bh_remove_min(BHeap *bh);

/**
 * Return the minimum element contained in the heap, or NULL if the heap is empty.
 *
 * @param bh Pointer to the binary heap data structure.
 * @return The minimum element contained in the heap, or NULL if the heap is empty.
 */
void *bh_peek(BHeap *bh);

#endif // _B_HEAP_H
