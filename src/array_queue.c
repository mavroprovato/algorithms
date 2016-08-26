#include "array_queue.h"

#include <stdlib.h>

/** The default queue size */
#define DEFALUT_SIZE 16;

/**
 * Initialize the queue data structure.
 *
 * @param al Pointer to the queue data structure.
 * @param size The initial size of the queue. If zero, the default value is
 * used.
 */
void aq_init(ArrayQueue *al, size_t size) {
    if (size > 0) {
        al->size = size;
    } else {
        al->size = DEFALUT_SIZE;
    }
    al->capacity = al->size;
    al->items = malloc(sizeof(void *) * al->size);
}

/**
 * Frees resources associated with the queue data structure.
 *
 * @param al Pointer to the queue data structure to be freed.
 */
void aq_destroy(ArrayQueue *al) {
    free(al->items);
}

/**
 * Check if the queue contains any elements.
 *
 * @param al Pointer to the queue data structure.
 * @return true if the queue contains elements, false otherwise.
 */
bool aq_is_empty(ArrayQueue *al) {
    return al->size == 0;
}

/**
 * Return the size of the array queue.
 *
 * @return The size of the array queue.
 */
size_t aq_size(ArrayQueue *al) {
    return al->size;
}
