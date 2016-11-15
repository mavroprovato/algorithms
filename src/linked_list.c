#include <stdlib.h>

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

/**
 * Add an element to the beginning of the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to add to the list.
 * @return true if the element was added, false otherwise.
 */
bool ll_add_first(LinkedList *ll, void *item) {
    // Create the node
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    if (!node) {
        return false;
    }
    node->item = item;

    // Add it to the head of the list.
    node->next = ll->head;
    ll->head = node;
    ll->size++;

    return true;
}

/**
 * Append an element to the end of the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to append to the list.
 * @return true if the element was added, false otherwise.
 */
bool ll_append(LinkedList *ll, void *item) {
    // Create the node
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    if (!node) {
        return false;
    }
    node->item = item;
    node->next = NULL;

    // Append it to the end of the list.
    LinkedListNode *current = ll->head;
    if (current) {
        while (current->next) {
            current = current->next;
        }
        current->next = node;
    } else {
        current = node;
    }
    ll->size++;

    return true;
}

/**
 * Add an element to a specific position in the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to add to the list.
 * @param index The index at which the element will be added.
 * @return true if the element was added, false otherwise.
 */
bool ll_add(LinkedList *ll, void *item, size_t index) {
    // Check bounds
    if (index >= ll->size) {
        return false;
    }

    // Create the node
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    if (!node) {
        return false;
    }
    node->item = item;
    node->next = NULL;

    // Add the element to the specified position it to the end of the list.
    LinkedListNode *current = ll->head;
    int current_index = 0;
    if (current) {
        while (current->next && current_index++ != index) {
            current = current->next;
        }
        current->next = node;
    } else {
        current = node;
    }
    ll->size++;

    return true;
}
