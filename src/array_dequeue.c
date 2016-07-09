#include "array_dequeue.h"

#include <stdlib.h>

/** The default dequeue size */
#define DEFALUT_SIZE 16;

/**
 * Initialize the dequeue data structure.
 *
 * @param al Pointer to the dequeue data structure.
 * @param size The initial size of the dequeue. If zero, the default value is used.
 */
void dq_init(ArrayDequeue *al, size_t size) {
    if (size > 0) {
        al->size = size;
    } else {
        al->size = DEFALUT_SIZE;
    }
    al->capacity = al->size;
    al->items = malloc(sizeof(void *) * al->size);
}

/**
 * Frees resources associated with the dequeue data structure.
 *
 * @param al Pointer to the dequeue data structure to be freed.
 */
void dq_destroy(ArrayDequeue *al) {
    free(al->items);
}

/**
 * Check if the dequeue contains any elements.
 *
 * @param al Pointer to the dequeue data structure.
 * @return true if the dequeue contains elements, false otherwise.
 */
bool dq_is_empty(ArrayDequeue *al) {
    return al->size == 0;
}
