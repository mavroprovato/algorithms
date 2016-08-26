#ifndef _ARRAY_QUEUE
#define _ARRAY_QUEUE

#include <stddef.h>
#include <stdbool.h>

/**
 * The queue data structure, backed by an array.
 */
typedef struct {
    /** The queue elements. */
    void *items;
    /** The queue size. */
    size_t size;
    /** The current capacity of the queue */
    size_t capacity;
} ArrayQueue;

/**
 * Initialize the array queue data structure.
 *
 * @param al Pointer to the array queue data structure.
 * @param size The initial size of the queue. If zero, the default value is
 * used.
 */
void aq_init(ArrayQueue *al, size_t size);

/**
 * Frees resources associated with the array queue data structure.
 *
 * @param al Pointer to the array queue data structure to be freed.
 */
void aq_destroy(ArrayQueue *al);

/**
 * Check if the queue contains any elements.
 *
 * @param al Pointer to the array queue data structure.
 * @return true if the queue contains elements, false otherwise.
 */
bool aq_is_empty(ArrayQueue *al);

/**
 * Return the size of the array queue.
 *
 * @return The size of the array queue.
 */
size_t aq_size(ArrayQueue *al);


#endif // _ARRAY_QUEUE
