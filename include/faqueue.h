#ifndef _FA_QUEUE_H
#define _FA_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

#include "common.h"

/**
 * The queue data structure, backed by an fixed-sized array.
 */
typedef struct {
    /** The queue elements. */
    void **items;
    /** The queue size. */
    size_t size;
    /** The capacity of the queue. */
    size_t capacity;
    /** The index of the first element of the queue. */
    size_t head;
    /** The index of the last element of the queue. */
    size_t tail;
} FAQueue;

/**
 * Initialize the fixed array queue.
 *
 * @param faq Pointer to the fixed array queue data structure.
 * @param capacity The maximum capacity of the queue.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool faq_init(FAQueue *faq, size_t capacity);

/**
 * Free resources associated with the fixed array queue.
 *
 * @param faq Pointer to the fixed array queue data structure to be freed.
 */
void faq_destroy(FAQueue *faq);

/**
 * Check if the fixed array queue contains elements.
 *
 * @param faq Pointer to the fixed array queue data structure.
 * @return true if the queue contains elements, false otherwise.
 */
bool faq_is_empty(FAQueue *faq);

/**
 * Return the size of the fixed array queue.
 *
 * @param faq Pointer to the fixed array queue data structure.
 * @return The size of the fixed array queue.
 */
size_t faq_size(FAQueue *faq);

/**
 * Add an element to the fixed array queue. Note that NULL elements cannot be
 * added to the queue.
 *
 * @param faq Pointer to the fixed array queue data structure.
 * @param item Pointer to the item to add to the fixed array queue.
 * @return true if the element was enqueued successfully, false otherwise.
 */
bool faq_enqueue(FAQueue *faq, void *item);

/**
 * Removes and returns the least recently added fixed array queue element.
 *
 * @param faq Pointer to the fixed array queue data structure.
 * @return The least recently added fixed array queue element or NULL if the
 * queue was empty.
 */
void *faq_dequeue(FAQueue *faq);

/**
 * Returns the least recently added fixed array queue element.
 *
 * @param faq Pointer to the fixed array queue data structure.
 * @return The least recently added fixed array queue element or NULL if the
 * queue was empty.
 */
void *faq_peek(FAQueue *faq);

/**
 * Traverse all the items of the fixed array queue and call a function for each
 * of them.
 *
 * @param faq Pointer to the fixed array queue data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void faq_foreach(FAQueue *faq, ITERATOR_FUNC iterator_func, void *data);

#endif // _FA_QUEUE_H
