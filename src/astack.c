#include "astack.h"

#include <stdlib.h>
#include <string.h>

/**
 * Resize the underlying array holding the stack items.
 *
 * @param as Pointer to the stack data structure.
 * @param new_capacity The new capacity.
 * @return true if the resizing was successful, false otherwise.
 */
static bool as_resize(AStack *as, size_t new_capacity) {
    // Allocate the new array
    void *new_items = malloc(new_capacity * sizeof(void *));
    if (!new_items) {
        return false;
    }

    // Copy the items to the new array.
    memcpy(new_items, as->items, as->size * sizeof(void *));

    free(as->items);
    as->items = new_items;
    as->capacity = new_capacity;

    return true;
}

bool as_init(AStack *as) {
    as->capacity = 2;
    as->items = malloc(as->capacity * sizeof(void *));
    if (!as->items) {
        return false;
    }
    as->size = 0;

    return true;
}

void as_destroy(AStack *as) {
    // Free the underlying array
    free(as->items);
    as->items = NULL;
}

bool as_is_empty(AStack *as) {
    return as->size == 0;
}

size_t as_size(AStack *as) {
    return as->size;
}

bool as_push(AStack *as, void *item) {
    if (as->size == as->capacity) {
        // The array needs to be expanded
        if (!as_resize(as, 2 * as->capacity)) {
            return false;
        }
    }
    as->items[as->size++] = item;

    return true;
}

void *as_pop(AStack *as) {
    if (as->size == 0) {
        // The array is empty
        return NULL;
    }

    void *item = as->items[as->size - 1];
    as->items[as->size - 1] = NULL;
    as->size--;

    if (as->size > 0 && as->size == as->capacity / 4) {
        // The array needs to be shrinked
        as_resize(as, as->capacity / 2);
    }

    return item;
}

void *as_peek(AStack *as) {
    if (as->size == 0) {
        // The array is empty
        return NULL;
    }

    return as->items[as->size - 1];
}

void as_foreach(AStack *as, ITERATOR_FUNC iterator_func, void *data) {
    for (size_t i = as->size; i-- > 0; ) {
        iterator_func(as->items[i], data);
    }
}
