#include "array_queue.h"

#include <stdlib.h>
#include <string.h>

/** The default queue size */
#define DEFALUT_SIZE 16;

/**
 * Resize the underlying array with the queue items.
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
    if (aq->first > aq->last) { // The array has wrapped around.
        memcpy(new_items, aq->items + aq->first,
           (aq->capacity - aq->first) * sizeof(void *));
        memcpy(new_items + (aq->capacity - aq->first), aq->items,
               (aq->last + 1) * sizeof(void *));
    } else {
        memcpy(new_items, aq->items + aq->first,
           (aq->last - aq->first) * sizeof(void *));
    }

    free(aq->items);
    aq->items = new_items;
    aq->capacity = new_capacity;
    aq->first = 0;
    aq->last = aq->size;

    return true;
}

/**
 * Initialize the queue data structure.
 *
 * @param aq Pointer to the queue data structure.
 * @param size The initial capacity of the queue. If zero, the default value is
 * used.
 */
void aq_init(ArrayQueue *aq, size_t size) {
    if (size > 0) {
        aq->capacity = size;
    } else {
        aq->capacity = DEFALUT_SIZE;
    }
    aq->size = 0;
    aq->items = malloc(aq->capacity * sizeof(void *));
    aq->first = 0;
    aq->last = 0;
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
void aq_enqueue(ArrayQueue *aq, void *item) {
    if (aq->size == aq->capacity) {
        aq_resize(aq, 2 * aq->capacity);
    }
    aq->items[aq->last++] = item;
    if (aq->last > aq->capacity) { // wrap around
        aq->last = 0;
    }
    aq->size++;
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

    void *item = aq->items[aq->first];
    aq->items[aq->first] = NULL;
    aq->size--;
    aq->first++;
    if (aq->first > aq->capacity) { // wrap aroung
        aq->first = 0;
    }

    if (aq->size > 0 && aq->size == aq->capacity / 4) {
        aq_resize(aq, aq->capacity / 4);
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

    return aq->items[aq->first];
}
