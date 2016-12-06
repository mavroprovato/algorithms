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
bool ll_prepend(LinkedList **ll, void *item) {
    // Alocate the node
    LinkedList *new_ll = ll_create(item);
    if (!new_ll) {
        return false;
    }

    // Put it at the start of the list
    new_ll->next = *ll;
    *ll = new_ll;

    return true;
}

/**
 * Add an item as the last element of the list.
 *
 * @param ll The linked list data structure.
 * @param item Pointer to the item to add.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool ll_append(LinkedList **ll, void *item) {
    // Alocate the node
    LinkedList *new_ll = ll_create(item);
    if (!new_ll) {
        return false;
    }

    // If it is an empty list, return the created node
    if (!*ll) {
        *ll = new_ll;
    } else {
        LinkedList *current = *ll;
        while (current->next) {
            current = current->next;
        }
        current->next = new_ll;
    }

    return true;
}

/**
 * Insert an item at the specified position of the list.
 *
 * @param ll The linked list data structure.
 * @param item Pointer to the item to add.
 * @param position The position at which the element is to be inserted.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool ll_insert(LinkedList **ll, void *item, size_t position) {
    // If empty or position is zero, call prepend.
    if (!*ll || position == 0) {
        return ll_prepend(ll, item);
    }

    // Alocate the node
    LinkedList *new_ll = ll_create(item);
    if (!new_ll) {
        return false;
    }

    // Put it at the requested position
    LinkedList *current = *ll;
    size_t index = 0;
    while (current->next && index++ < position - 1) {
        current = current->next;
    }
    new_ll->next = current->next;
    current->next = new_ll;

    return true;
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
