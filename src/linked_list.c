#include <stdlib.h>

#include "linked_list.h"

/**
 * Create a linked list structure.
 *
 * @param item Pointer to the item to hold.
 * @return The created linked list structure or NULL if the stuructre could not
 * be created.
 */
LinkedList *ll_create(void *item) {
    LinkedList *ll = malloc(sizeof(LinkedList));
    if (!ll) {
        return NULL;
    }
    ll->item = item;
    ll->next = NULL;

    return ll;
}

/**
 * Destroy the linked list structure.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to hold.
 */
void ll_destroy(LinkedList *ll) {
    free(ll);
}

/**
 * Return the size of the linked list.
 *
 * @param ll Pointer to the linked list data structure.
 * @return The size of the linked list.
 */
size_t ll_size(LinkedList *ll) {
    size_t size = 0;
    LinkedList *current = ll;
    while (current) {
        current = current->next;
        size++;
    }

    return size;
}

/**
 * Check if the linked list is empty.
 *
 * @param ll Pointer to the linked list data structure.
 * @return true if the linked list is empty, false otherwise.
 */
bool ll_is_empty(LinkedList *ll) {
    return ll == NULL;
}

/**
 * Add an item as the first element of the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to add.
 * @return Pointer to the updated list or NULL if the list cannot be updated.
 */
LinkedList *ll_prepend(LinkedList *ll, void *item) {
    LinkedList *new_ll = ll_create(item);
    if (new_ll) {
        new_ll->next = ll;
    }

    return new_ll;
}

/**
 * Add an item as the last element of the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to add.
 * @return Pointer to the updated list or NULL if the list cannot be updated.
 */
LinkedList *ll_append(LinkedList *ll, void *item) {
    LinkedList *new_ll = ll_create(item);
    if (!new_ll) {
        return NULL;
    }
    if (!ll) {
        return new_ll;
    }
    LinkedList *current = ll;
    while (current->next) {
        current = current->next;
    }
    current->next = new_ll;

    return ll;
}

/**
 * Insert an item at the specified position of the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to add.
 * @param position The position at which the element is to be inserted.
 * @return Pointer to the updated list or NULL if the list cannot be updated.
 */
LinkedList *ll_insert(LinkedList *ll, void *item, size_t position) {
    if (!ll || position == 0) {
        return ll_prepend(ll, item);
    }
    LinkedList *new_ll = ll_create(item);
    if (!new_ll) {
        return NULL;
    }
    LinkedList *current = ll;
    size_t index = 0;
    while (current->next && index++ < position - 1) {
        current = current->next;
    }
    new_ll->next = current->next;
    current->next = new_ll;

    return ll;
}


/**
 * Add an item as the last element of the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void ll_foreach(LinkedList *ll, ITERATOR_FUNC iterator_func, void *data) {
    LinkedList *current = ll;
    while (current) {
        iterator_func(current->item, data);
        current = current->next;
    }
}
