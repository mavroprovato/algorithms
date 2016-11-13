#ifndef _ARRAY_QUEUE
#define _ARRAY_QUEUE

#include <stddef.h>
#include <stdbool.h>

/**
 * The queue data structure, backed by an array.
 */
typedef struct {
    /** The queue elements. */
    void **items;
    /** The queue size. */
    size_t size;
    /** The current capacity of the queue */
    size_t capacity;
    /** The first element on the queue */
    size_t head;
    /** The last element on the queue */
    size_t tail;
} ArrayQueue;

/**
 * Initialize the queue data structure.
 *
 * @param aq Pointer to the queue data structure.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool aq_init(ArrayQueue *aq);

/**
 * Frees resources associated with the array queue data structure.
 *
 * @param aq Pointer to the array queue data structure to be freed.
 */
void aq_destroy(ArrayQueue *aq);

/**
 * Check if the queue contains any elements.
 *
 * @param aq Pointer to the array queue data structure.
 * @return true if the queue contains elements, false otherwise.
 */
bool aq_is_empty(ArrayQueue *aq);

/**
 * Return the size of the array queue.
 *
 * @param aq Pointer to the array queue data structure.
 * @return The size of the array queue.
 */
size_t aq_size(ArrayQueue *aq);

/**
 * Add an element to the queue.
 *
 * @param aq Pointer to the queue data structure.
 * @param item Pointer to the item to add to the queue.
 */
void aq_enqueue(ArrayQueue *aq, void *item);

/**
 * Removes and returns the least recent element that was added to the queue.
 *
 * @param aq Pointer to the queue data structure.
 * @return The least recent element that was added to the queue.
 */
void *aq_dequeue(ArrayQueue *aq);

/**
 * Returns the least recent element that was added to the queue.
 *
 * @param aq Pointer to the queue data structure.
 * @return The least recent element that was added to the queue.
 */
void *aq_peek(ArrayQueue *aq);

#endif // _ARRAY_QUEUE
