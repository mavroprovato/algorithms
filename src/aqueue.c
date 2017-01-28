#include "aqueue.h"

#include <stdlib.h>
#include <string.h>

/**
 * Resize the underlying array holding the queue items.
 *
 * @param aq Pointer to the queue data structure.
 * @param new_capacity The new capacity.
 * @return true if the resizing was successful, false otherwise.
 */
static bool aq_resize(AQueue *aq, size_t new_capacity) {
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

bool aq_init(AQueue *aq) {
    aq->capacity = 2;
    aq->items = malloc(aq->capacity * sizeof(void *));
    if (!aq->items) {
        return false;
    }
    aq->size = 0;
    aq->head = 0;
    aq->tail = 0;

    return true;
}

void aq_destroy(AQueue *aq) {
    free(aq->items);
    aq->items = NULL;
}

bool aq_is_empty(AQueue *aq) {
    return aq->size == 0;
}

size_t aq_size(AQueue *aq) {
    return aq->size;
}

bool aq_enqueue(AQueue *aq, void *item) {
    if (!item) {
        // NULL items cannot be added
        return false;
    }
    if (aq->size == aq->capacity) {
        // The item array needs to be resized
        if (!aq_resize(aq, 2 * aq->capacity)) {
            return false;
        }
    }
    aq->items[aq->tail++] = item;
    if (aq->tail == aq->capacity) {
         // Wrap around
        aq->tail = 0;
    }
    aq->size++;

    return true;
}

void *aq_dequeue(AQueue *aq) {
    if (aq->size == 0) {
        // The queue is empty
        return NULL;
    }

    void *item = aq->items[aq->head];
    aq->items[aq->head] = NULL;
    aq->size--;
    aq->head++;
    if (aq->head == aq->capacity) {
        // Wrap around
        aq->head = 0;
    }

    if (aq->size > 0 && aq->size == aq->capacity / 4) {
        // Shrink the item array
        aq_resize(aq, aq->capacity / 2);
    }

    return item;
}

void *aq_peek(AQueue *aq) {
    if (aq->size == 0) {
        // The queue is empty
        return NULL;
    }

    return aq->items[aq->head];
}

void aq_foreach(AQueue *aq, ITERATOR_FUNC iterator_func, void *data) {
    if (aq->head <= aq->tail) {
        for (size_t i = aq->head; i < aq->tail; i++) {
            iterator_func(aq->items[i], data);
        }
    } else {
        // The array has wrapped around.
        for (size_t i = aq->head; i < aq->capacity; i++) {
            iterator_func(aq->items[i], data);
        }
        for (size_t i = 0; i < aq->tail; i++) {
            iterator_func(aq->items[i], data);
        }
    }
}
