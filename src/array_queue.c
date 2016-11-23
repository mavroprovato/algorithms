#include "array_queue.h"

#include <stdlib.h>
#include <string.h>

/**
 * Resize the underlying array holding the queue items.
 *
 * @param aq Pointer to the queue data structure.
 * @param new_capacity The new capacity.
 * @return true if the resizing was successful, false otherwise.
 */
static bool aq_resize(ArrayQueue *aq, size_t new_capacity) {
    // Allocate the new array
    void *new_items = malloc(new_capacity * sizeof(void *));
    if (!new_items) {
        return false;
    }

    // Copy the items to the new array.
    if (aq->head < aq->tail) {
        memcpy(new_items, aq->items + aq->head,
               (aq->tail - aq->head) * sizeof(void *));
    } else { // The array has wrapped around.
        memcpy(new_items, aq->items + aq->head,
               (aq->capacity - aq->head) * sizeof(void *));
        memcpy((char *) new_items + (aq->capacity - aq->head) * sizeof(void *),
               aq->items, aq->tail * sizeof(void *));
    }

    free(aq->items);
    aq->items = new_items;
    aq->capacity = new_capacity;
    aq->head = 0;
    aq->tail = aq->size;

    return true;
}

/**
 * Initialize the queue data structure.
 *
 * @param aq Pointer to the queue data structure.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool aq_init(ArrayQueue *aq) {
    aq->capacity = 2;
    aq->size = 0;
    aq->items = malloc(aq->capacity * sizeof(void *));
    if (!aq->items) {
        return false;
    }
    aq->head = 0;
    aq->tail = 0;

    return true;
}

/**
 * Frees resources associated with the queue data structure.
 *
 * @param aq Pointer to the queue data structure to be freed.
 */
void aq_destroy(ArrayQueue *aq) {
    free(aq->items);
}

/**
 * Check if the queue contains any elements.
 *
 * @param aq Pointer to the queue data structure.
 * @return true if the queue contains elements, false otherwise.
 */
bool aq_is_empty(ArrayQueue *aq) {
    return aq->size == 0;
}

/**
 * Return the size of the array queue.
 *
 * @return The size of the array queue.
 */
size_t aq_size(ArrayQueue *aq) {
    return aq->size;
}

/**
 * Add an element to the queue.
 *
 * @param aq Pointer to the queue data structure.
 * @param item Pointer to the item to add to the queue.
 */
bool aq_enqueue(ArrayQueue *aq, void *item) {
    if (aq->size == aq->capacity) {
        if (!aq_resize(aq, 2 * aq->capacity)) {
            return false;
        }
    }
    aq->items[aq->tail++] = item;
    if (aq->tail == aq->capacity) { // wrap around
        aq->tail = 0;
    }
    aq->size++;

    return true;
}

/**
 * Removes and returns the last element that was added to the queue.
 *
 * @param aq Pointer to the queue data structure.
 */
void *aq_dequeue(ArrayQueue *aq) {
    if (aq_is_empty(aq)) {
        return NULL;
    }

    void *item = aq->items[aq->head];
    aq->items[aq->head] = NULL;
    aq->size--;
    aq->head++;
    if (aq->head == aq->capacity) { // wrap aroung
        aq->head = 0;
    }

    if (aq->size > 0 && aq->size == aq->capacity / 4) {
        aq_resize(aq, aq->capacity / 2);
    }

    return item;
}

/**
 * Returns the last element that was added to the queue.
 *
 * @param aq Pointer to the queue data structure.
 * @return The last element that was added to the queue.
 */
void *aq_peek(ArrayQueue *aq) {
    if (aq_is_empty(aq)) {
        return NULL;
    }

    return aq->items[aq->head];
}
