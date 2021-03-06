#ifndef _L_QUEUE_H
#define _L_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

#include "common.h"

/**
 * The linked stack node.
 */
typedef struct LQueueNode {
    /** The item. */
    void *item;
    /** The next node. */
    struct LQueueNode *next;
} LQueueNode;

/**
 * The queue data structure, backed by a linked list.
 */
typedef struct {
    /** The head of the queue. */
    LQueueNode *head;
    /** The tail of the queue. */
    LQueueNode *tail;
    /** The queue size. */
    size_t size;
} LQueue;

/**
 * Initialize the linked queue data structure.
 *
 * @param lq Pointer to the linked queue data structure.
 * @return true if the linked queue data structure was initialized successfully, false otherwise.
 */
bool lq_init(LQueue *lq);

/**
 * Frees resources associated with the linked queue data structure.
 *
* @param lq Pointer to the linked queue data structure to be freed.
 */
void lq_destroy(LQueue *lq);

/**
 * Check if the linked queue contains any elements.
 *
 * @param lq Pointer to the linked queue data structure.
 * @return true if the linked queue contains elements, false otherwise.
 */
bool lq_is_empty(LQueue *lq);

/**
 * Return the size of the linked queue.
 *
 * @param lq Pointer to the linked queue data structure.
 * @return The size of the linked queue.
 */
size_t lq_size(LQueue *lq);

/**
 * Add an element to the linked queue.
 *
 * @param lq Pointer to the linked queue data structure.
 * @param item Pointer to the item to add to the queue. Note that NULL elements cannot be added to the queue.
 * @return true if the element was enqueued successfully, false otherwise.
 */
bool lq_enqueue(LQueue *lq, void *item);

/**
 * Removes and returns the least recent element that was added to the linked
 * queue.
 *
 * @param lq Pointer to the linkedqueue data structure.
 * @return The least recent element that was added to the linked queue, or NULL if the queue was empty.
 */
void *lq_dequeue(LQueue *lq);

/**
 * Returns the least recent element that was added to the linked queue.
 *
 * @param lq Pointer to the linked queue data structure.
 * @return The least recent element that was added to the linked queue, or NULL if the queue was empty.
 */
void *lq_peek(LQueue *lq);

/**
 * Traverse all the items of the linked queue and call a function for each of them.
 *
 * @param lq Pointer to the linked queue data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void lq_foreach(LQueue *lq, ITERATOR_FUNC iterator_func, void *data);

#endif // _L_QUEUE_H
