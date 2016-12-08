#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include "util.h"

#include <sys/types.h>

#include <stdbool.h>
#include <stddef.h>

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
 * Remove an item from the list.
 *
 * @param ll The linked list data structure.
 * @param item The position at which the element is to be inserted.
 * @return The item that was removed, or NULL if the item was not found.
 */
void *ll_remove_item(LinkedList **ll, void *item, COMPARE_FUNC compare_func);

/**
 * Add an item as the last element of the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void ll_foreach(LinkedList *ll, ITERATOR_FUNC iterator_func, void *data);

/**
 * Check if the linked list contains an element.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare items.
 * @return The index of the item, or -1 if the item is not found.
 */
bool ll_contains(LinkedList *ll, void *item, COMPARE_FUNC compare_func);

/**
 * Search for an element and return its index in the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare items.
 * @return The index of the item, or -1 if the item is not found.
 */
ssize_t ll_find(LinkedList *ll, void *item, COMPARE_FUNC compare_func);

/**
 * Reverse the linked list.
 *
 * @param ll The linked list data structure.
 */
void ll_reverse(LinkedList **ll);

#endif // _LINKED_LIST_H
