#ifndef _LINKED_LIST
#define _LINKED_LIST

#include <stdbool.h>
#include <stddef.h>

/**
 * Prototype for a function used to iterate the linked list.
 *
 * @param item The current item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
typedef void (*ITERATOR_FUNC) (void *item, void *data);

/**
 * The linked list structure.
 */
typedef struct LinkedList {
    /** The item. */
    void *item;
    /** The next node. */
    struct LinkedList *next;
} LinkedList;

/**
 * Create a linked list structure.
 *
 * @param item Pointer to the item to hold.
 * @return The created linked list structure or NULL if the stuructre could not
 * be created.
 */
LinkedList *ll_create(void *item);

/**
 * Destroy the linked list structure.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to hold.
 */
void ll_destroy(LinkedList *ll);

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
 * Add an item as the first element of the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to add.
 * @return Pointer to the updated list or NULL if the list cannot be updated.
 */
bool ll_prepend(LinkedList **ll, void *item);

/**
 * Add an item as the last element of the list.
 *
 * @param ll The linked list data structure.
 * @param item Pointer to the item to add.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool ll_append(LinkedList **ll, void *item);

/**
 * Insert an item at the specified position of the list.
 *
 * @param ll The linked list data structure.
 * @param item Pointer to the item to add.
 * @param position The position at which the element is to be inserted.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool ll_insert(LinkedList **ll, void *item, size_t position);

/**
 * Remove the first item of the list.
 *
 * @param ll The linked list data structure.
 * @return The item that was removed.
 */
void *ll_remove_first(LinkedList **ll);

/**
 * Remove the last item of the list.
 *
 * @param ll The linked list data structure.
 * @return The item that was removed.
 */
void *ll_remove_last(LinkedList **ll);

/**
 * Remove an item from the list by position.
 *
 * @param ll The linked list data structure.
 * @param position The position at which the element is to be inserted.
 * @return The item that was removed.
 */
void *ll_remove(LinkedList **ll, size_t position);

/**
 * Add an item as the last element of the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void ll_foreach(LinkedList *ll, ITERATOR_FUNC iterator_func, void *data);

#endif // _LINKED_LIST
