#include "linked_list.h"

#include <stdlib.h>

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
 * Remove the first item of the list.
 *
 * @param ll The linked list data structure.
 * @return The item that was removed.
 */
void *ll_remove_first(LinkedList **ll) {
    // If list is empty return null.
    if (!*ll) {
        return NULL;
    }

    // Point the node to the next item and free resources.
    void *item = (*ll)->item;
    LinkedList *current = *ll;
    *ll = (*ll)->next;
    free(current);

    return item;
}

/**
 * Remove the last item of the list.
 *
 * @param ll The linked list data structure.
 * @return The item that was removed.
 */
void *ll_remove_last(LinkedList **ll) {
    // If list is empty return null.
    if (!*ll) {
        return NULL;
    }

    // Find and remove the last node
    LinkedList *current = *ll;
    while (current->next && current->next->next) {
        current = current->next;
    }
    void *item = NULL;
    if (current->next == NULL) { // Only one item in the list
        item = current->item;
        (*ll) = NULL;
        free(current);
    } else {
        item = current->next->item;
        free(current->next);
        current->next = NULL;
    }

    return item;
}

/**
 * Remove an item from the list by position.
 *
 * @param ll The linked list data structure.
 * @param position The position at which the element is to be inserted.
 * @return The item that was removed.
 */
void *ll_remove(LinkedList **ll, size_t position) {
    // If list is empty return null.
    if (!*ll || position == 0) {
        return ll_remove_first(ll);
    }

    // Find and remove the node
    LinkedList *current = *ll;
    size_t index = 0;
    while (current->next && current->next->next && index++ < position - 1) {
        current = current->next;
    }
    void *item = NULL;
    if (current->next == NULL) { // The last element of the list
        item = current->item;
        (*ll) = NULL;
        free(current);
    } else {
        LinkedList *node = current->next;
        item = node->item;
        current->next = current->next->next;
        free(node);
    }

    return item;
}

/**
 * Remove an item from the list.
 *
 * @param ll The linked list data structure.
 * @param item The position at which the element is to be inserted.
 * @return The item that was removed, or NULL if the item was not found.
 */
void *ll_remove_item(LinkedList **ll, void *item, COMPARE_FUNC compare_func) {
    if (!*ll) { // Empty list
        return NULL;
    }

    // Search for the item
    LinkedList *current = *(ll);
    LinkedList *previous = NULL;
    while (current && compare_func(current->item, item) != 0) {
        previous = current;
        current = current->next;
    }

    if (current) { // Found
        void *found = current->item;
        if (previous) {
            previous->next = current->next;
        } else {
            (*ll) = NULL;
        }
        free(current);

        return found;
    }

    // Not found
    return NULL;
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

/**
 * Check if the linked list contains an element.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare items.
 * @return The index of the item, or -1 if the item is not found.
 */
bool ll_contains(LinkedList *ll, void *item, COMPARE_FUNC compare_func) {
    return ll_find(ll, item, compare_func) != -1;
}

/**
 * Search for an element and return its index in the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare items.
 * @return The index of the item, or -1 if the item is not found.
 */
ssize_t ll_find(LinkedList *ll, void *item, COMPARE_FUNC compare_func) {
    ssize_t pos = 0;

    LinkedList *current = ll;
    while (current && compare_func(current->item, item) != 0) {
        pos++;
        current = current->next;
    }

    return current == NULL ? -1 : pos;
}

/**
 * Reverse the linked list.
 *
 * @param ll The linked list data structure.
 */
void ll_reverse(LinkedList **ll) {
    if (!*ll || !(*ll)->next) {
        // Less than two elements, no need to do anything
        return;
    }

    LinkedList *previous = NULL;
    LinkedList *current = *ll;
    LinkedList *next = (*ll)->next;

    while (current) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    *ll = previous;
}
