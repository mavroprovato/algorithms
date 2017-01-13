#ifndef _LINKED_QUEUE_H
#define _LINKED_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

#include "util.h"
#include "linked_list.h"

/**
 * The queue data structure, backed by a linked list.
 */
typedef struct {
    /** The head of the queue. */
    LinkedList *head;
    /** The tail of the queue. */
    LinkedList *tail;
    /** The queue size. */
    size_t size;
} LinkedQueue;

/**
 * Initialize the queue data structure.
 *
 * @param lq Pointer to the queue data structure.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool lq_init(LinkedQueue *lq);

/**
 * Frees resources associated with the array queue data structure.
 *
 * @param lq Pointer to the array queue data structure to be freed.
 */
void lq_destroy(LinkedQueue *lq);

/**
 * Check if the queue contains any elements.
 *
 * @param lq Pointer to the array queue data structure.
 * @return true if the queue contains elements, false otherwise.
 */
bool lq_is_empty(LinkedQueue *lq);

/**
 * Return the size of the array queue.
 *
 * @param lq Pointer to the array queue data structure.
 * @return The size of the array queue.
 */
size_t lq_size(LinkedQueue *lq);

/**
 * Add an element to the queue.
 *
 * @param lq Pointer to the queue data structure.
 * @param item Pointer to the item to add to the queue.
 * @return true if the element was enqueued successfully, false otherwise.
 */
bool lq_enqueue(LinkedQueue *lq, void *item);

/**
 * Removes and returns the least recent element that was added to the queue.
 *
 * @param lq Pointer to the queue data structure.
 * @return The least recent element that was added to the queue.
 */
void *lq_dequeue(LinkedQueue *lq);

/**
 * Returns the least recent element that was added to the queue.
 *
 * @param lq Pointer to the queue data structure.
 * @return The least recent element that was added to the queue.
 */
void *lq_peek(LinkedQueue *lq);

/**
 * Traverse all the items of the queue and call a function for each of them.
 *
 * @param lq Pointer to the queue data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void lq_foreach(LinkedQueue *lq, ITERATOR_FUNC iterator_func, void *data);

#endif // _LINKED_QUEUE_H
