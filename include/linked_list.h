#ifndef _LINKED_LIST
#define _LINKED_LIST

#include <stdbool.h>
#include <stddef.h>

/**
 * The linked list node.
 */
typedef struct {
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

#endif // _LINKED_LIST
