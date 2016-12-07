#include "array_stack.h"

#include <stdlib.h>
#include <string.h>

/**
 * Resize the underlying array holding the stack items.
 *
 * @param as Pointer to the stack data structure.
 * @param new_capacity The new capacity.
 * @return true if the resizing was successful, false otherwise.
 */
static bool as_resize(ArrayStack *as, size_t new_capacity) {
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

/**
 * Initialize the stack data structure.
 *
 * @param as Pointer to the stack data structure.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool as_init(ArrayStack *as) {
    as->capacity = 2;
    as->items = malloc(as->capacity * sizeof(void *));
    if (!as->items) {
        return false;
    }
    as->size = 0;

    return true;
}

/**
 * Frees resources associated with the array stack data structure.
 *
 * @param as Pointer to the array stack data structure to be freed.
 */
void as_destroy(ArrayStack *as) {
    free(as->items);
}

/**
 * Check if the stack contains any elements.
 *
 * @param as Pointer to the array stack data structure.
 * @return true if the stack contains elements, false otherwise.
 */
bool as_is_empty(ArrayStack *as) {
    return as->size == 0;
}

/**
 * Return the size of the array stack.
 *
 * @param as Pointer to the array stack data structure.
 * @return The size of the array stack.
 */
size_t as_size(ArrayStack *as) {
    return as->size;
}

/**
 * Add an element to the stack.
 *
 * @param as Pointer to the stack data structure.
 * @param item Pointer to the item to add to the stack.
 */
bool as_push(ArrayStack *as, void *item) {
    if (as->size == as->capacity) {
        if(!as_resize(as, 2 * as->capacity)) {
            return false;
        }
    }

    as->items[as->size++] = item;
    return true;
}

/**
 * Removes and returns the last element that was added to the stack.
 *
 * @param as Pointer to the stack data structure.
 * @return The last element that was added to the stack.
 */
void *as_pop(ArrayStack *as) {
    if (as_is_empty(as)) {
        return NULL;
    }

    void *item = as->items[as->size - 1];
    as->items[as->size - 1] = NULL;
    as->size--;

    if (as->size > 0 && as->size == as->capacity / 4) {
        as_resize(as, as->capacity / 2);
    }


    return item;
}

/**
 * Returns the last element that was added to the stack.
 *
 * @param as Pointer to the stack data structure.
 * @return The last element that was added to the stack.
 */
void *as_peek(ArrayStack *as) {
    if (as_is_empty(as)) {
        return NULL;
    }

    return as->items[as->size - 1];
}
