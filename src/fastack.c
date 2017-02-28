#include "fastack.h"

#include <stdlib.h>
#include <string.h>

bool fas_init(FAStack *fas, size_t capacity) {
    fas->capacity = capacity;
    fas->items = malloc(fas->capacity * sizeof(void *));
    if (!fas->items) {
        return false;
    }
    fas->size = 0;

    return true;
}

void fas_destroy(FAStack *fas) {
    // Free the underlying array
    free(fas->items);
    fas->items = NULL;
}

bool fas_is_empty(FAStack *fas) {
    return fas->size == 0;
}

size_t fas_size(FAStack *fas) {
    return fas->size;
}

bool fas_push(FAStack *fas, void *item) {
    if (fas->size == fas->capacity) {
        // Overflow
        return false;
    }
    fas->items[fas->size++] = item;

    return true;
}

void *fas_pop(FAStack *fas) {
    if (fas->size == 0) {
        // The array is empty
        return NULL;
    }

    void *item = fas->items[fas->size - 1];
    fas->items[fas->size - 1] = NULL;
    fas->size--;

    return item;
}

void *fas_peek(FAStack *fas) {
    if (fas->size == 0) {
        // The array is empty
        return NULL;
    }

    return fas->items[fas->size - 1];
}

void fas_foreach(FAStack *fas, ITERATOR_FUNC iterator_func, void *data) {
    for (size_t i = fas->size; i-- > 0; ) {
        iterator_func(fas->items[i], data);
    }
}
