#ifndef _LINKED_LIST
#define _LINKED_LIST

#include <stdbool.h>
#include <stddef.h>

/**
 * The linked list node.
 */
typedef struct LinkedListNode {
    /** The item. */
    void *item;
    /** The next node. */
    struct LinkedListNode *next;
} LinkedListNode;

/**
 * The linked list structure.
 */
typedef struct {
    /** Pointer to the first element of the list. */
    LinkedListNode *head;
    /** The size of the list. */
    size_t size;
} LinkedList;

/**
 * Initialize the linked list data structure.
 *
 * @param aq Pointer to the linked list data structure.
 * @return true if the data structure was initialize successfully,
 * false otherwise.
 */
bool ll_init(LinkedList *ll);

/**
 * Return the size of the linked list.
 *
 * @param ll Pointer to the linked list data structure.
 * @return The size of the linked list.
 */
size_t ll_size(LinkedList *ll);

/**
 * Check if the linked list is empty.
 *
 * @param ll Pointer to the linked list data structure.
 * @return true if the linked list is empty, false otherwise.
 */
bool ll_is_empty(LinkedList *ll);

/**
 * Add an element to the begining of the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to add to the list.
 * @return true if the element was added, false otherwise.
 */
bool ll_add_first(LinkedList *ll, void *item);

/**
 * Append an element to the end of the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to append to the list.
 * @return true if the element was added, false otherwise.
 */
bool ll_append(LinkedList *ll, void *item);

/**
 * Add an element to a specific position in the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to add to the list.
 * @param index The index at which the element will be added.
 * @return true if the element was added, false otherwise.
 */
bool ll_add(LinkedList *ll, void *item, size_t index);

#endif // _LINKED_LIST
