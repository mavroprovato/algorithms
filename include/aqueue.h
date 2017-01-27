#ifndef _A_QUEUE_H
#define _A_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

#include "common.h"

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
} AQueue;

/**
 * Initialize the queue data structure.
 *
 * @param aq Pointer to the queue data structure.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool aq_init(AQueue *aq);

/**
 * Frees resources associated with the queue data structure.
 *
 * @param aq Pointer to the queue data structure to be freed.
 */
void aq_destroy(AQueue *aq);

/**
 * Check if the queue contains any elements.
 *
 * @param aq Pointer to the queue data structure.
 * @return true if the queue contains elements, false otherwise.
 */
bool aq_is_empty(AQueue *aq);

/**
 * Return the size of the queue.
 *
 * @param aq Pointer to the queue data structure.
 * @return The size of the queue.
 */
size_t aq_size(AQueue *aq);

/**
 * Add an element to the queue.
 *
 * @param aq Pointer to the queue data structure.
 * @param item Pointer to the item to add to the queue.
 * @return true if the element was enqueued successfully, false otherwise.
 */
bool aq_enqueue(AQueue *aq, void *item);

/**
 * Removes and returns the least recent element that was added to the queue.
 *
 * @param aq Pointer to the queue data structure.
 * @return The least recent element that was added to the queue.
 */
void *aq_dequeue(AQueue *aq);

/**
 * Returns the least recent element that was added to the queue.
 *
 * @param aq Pointer to the queue data structure.
 * @return The least recent element that was added to the queue.
 */
void *aq_peek(AQueue *aq);

/**
 * Traverse all the items of the queue and call a function for each of them.
 *
 * @param aq Pointer to the queue data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void aq_foreach(AQueue *aq, ITERATOR_FUNC iterator_func, void *data);

#endif // _A_QUEUE_H
