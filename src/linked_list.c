#include "linked_list.h"

/**
 * Initialize the linked list data structure.
 *
 * @param ll Pointer to the linked list data structure.
 * @return true if the data structure was initialized successfully,
 * false otherwise.
 */
bool ll_init(LinkedList *ll) {
    ll->head = NULL;
    ll->size = 0;

    return true;
}

/**
 * Return the size of the linked list.
 *
 * @param ll Pointer to the linked list data structure.
 * @return The size of the linked list.
 */
size_t ll_size(LinkedList *ll) {
    return ll->size;
}

/**
 * Check if the linked list is empty.
 *
 * @param ll Pointer to the linked list data structure.
 * @return true if the linked list is empty, false otherwise.
 */
bool ll_is_empty(LinkedList *ll) {
    return ll->size == 0;
}
