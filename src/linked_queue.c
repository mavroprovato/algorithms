
#include "linked_queue.h"

/**
 * Initialize the queue data structure.
 *
 * @param lq Pointer to the queue data structure.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool lq_init(LinkedQueue *lq) {
    lq->head = NULL;
    lq->tail = NULL;
    lq->size = 0;

    return true;
}

/**
 * Frees resources associated with the array queue data structure.
 *
 * @param lq Pointer to the array queue data structure to be freed.
 */
void lq_destroy(LinkedQueue *lq) {
    ll_destroy(lq->head);
    ll_destroy(lq->tail);
}

/**
 * Check if the queue contains any elements.
 *
 * @param lq Pointer to the array queue data structure.
 * @return true if the queue contains elements, false otherwise.
 */
bool lq_is_empty(LinkedQueue *lq) {
    return lq->head == NULL;
}

/**
 * Return the size of the array queue.
 *
 * @param lq Pointer to the array queue data structure.
 * @return The size of the array queue.
 */
size_t lq_size(LinkedQueue *lq) {
    return lq->size;
}

/**
 * Add an element to the queue.
 *
 * @param lq Pointer to the queue data structure.
 * @param item Pointer to the item to add to the queue.
 * @return true if the element was enqueued successfully, false otherwise.
 */
bool lq_enqueue(LinkedQueue *lq, void *item) {
    if (!ll_append(&lq->tail, item)) {
        return false;
    }
    if (lq->tail->next) {
        lq->tail = lq->tail->next;
    }
    if (!lq->head) {
        lq->head = lq->tail;
    }

    return true;
}

/**
 * Removes and returns the least recent element that was added to the queue.
 *
 * @param lq Pointer to the queue data structure.
 * @return The least recent element that was added to the queue.
 */
void *lq_dequeue(LinkedQueue *lq) {
    void *item = NULL;
    if (lq->head) {
        item = ll_remove_first(&lq->head);
        if (!item) {
            return NULL;
        }
        lq->size--;
    }

    return item;
}

/**
 * Returns the least recent element that was added to the queue.
 *
 * @param lq Pointer to the queue data structure.
 * @return The least recent element that was added to the queue.
 */
void *lq_peek(LinkedQueue *lq) {
    return lq->head ? lq->head->item : NULL;
}

/**
 * Traverse all the items of the queue and call a function for each of them.
 *
 * @param lq Pointer to the queue data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void lq_foreach(LinkedQueue *lq, ITERATOR_FUNC iterator_func, void *data) {
    ll_foreach(lq->head, iterator_func, data);
}
