#ifndef _ARRAY_DEQUEUE
#define _ARRAY_DEQUEUE

#include <stddef.h>
#include <stdbool.h>

/**
 * The dequeue data structure, backed by an array.
 */
typedef struct {
    /** The dequeue elements. */
    void *items;
    /** The dequeue size. */
    size_t size;
    /** The current capacity of the dequeue */
    size_t capacity;
} ArrayDequeue;

/**
 * Initialize the array dequeue data structure.
 *
 * @param al Pointer to the array dequeue data structure.
 * @param size The initial size of the dequeue. If zero, the default value is
 * used.
 */
void dq_init(ArrayDequeue *al, size_t size);

/**
 * Frees resources associated with the array dequeue data structure.
 *
 * @param al Pointer to the array dequeue data structure to be freed.
 */
void dq_destroy(ArrayDequeue *al);

/**
 * Check if the dequeue contains any elements.
 *
 * @param al Pointer to the array dequeue data structure.
 * @return true if the dequeue contains elements, false otherwise.
 */
bool dq_is_empty(ArrayDequeue *al);


#endif // _ARRAY_DEQUEUE
