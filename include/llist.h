#ifndef _L_LIST_H
#define _L_LIST_H

#include "common.h"

#include <sys/types.h>

#include <stdbool.h>
#include <stddef.h>

/**
 * The linked list node.
 */
typedef struct LListNode {
    /** The item. */
    void *item;
    /** The next node. */
    struct LListNode *next;
} LListNode;

/**
 * The linked list data structure.
 */
typedef struct {
    /** The head list element. */
    LListNode *head;
} LList;

/**
 * Initialize the linked list data structure.
 *
 * @param ll Pointer to the linked list data structure to initialize.
 * @return true if the linked list data structure was initialized successfully,
 * false otherwise.
 */
bool ll_init(LList *ll);

/**
 * Frees resources associated with the linked list data structure.
 *
 * @param ll Pointer to the linked list data structure to be freed.
 */
void ll_destroy(LList *ll);

/**
 * Return the size of the linked list. In order to get the size, all the list
 * items are visited, so the performance of the function is linear.
 *
 * @param ll Pointer to the linked list data structure.
 * @return The size of the linked list.
 */
size_t ll_size(LList *ll);

/**
 * Check if the linked list is empty.
 *
 * @param ll Pointer to the linked list data structure.
 * @return true if the linked list is empty, false otherwise.
 */
bool ll_is_empty(LList *ll);

/**
 * Add an item as the first element of the linked list. Note that NULL items
 * cannot be added to the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to add.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool ll_prepend(LList *ll, void *item);

/**
 * Add an item as the last element of the linked list. Note that NULL items
 * cannot be added to the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to add.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool ll_append(LList *ll, void *item);

/**
 * Insert an item at the specified position of the linked list. Note that NULL
 * items cannot be added to the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item Pointer to the item to add.
 * @param position The position at which the element is to be inserted.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool ll_insert(LList *ll, void *item, size_t position);

/**
 * Remove the first item of the linked list.
 *
 * @param ll Pointer to the linked list data structure.
 * @return The item that was removed, or NULL if the linked list was empty.
 */
void *ll_remove_first(LList *ll);

/**
 * Remove the last item of the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @return The item that was removed, or NULL if the linked list was empty.
 */
void *ll_remove_last(LList *ll);

/**
 * Remove an item from the linked list by position.
 *
 * @param ll Pointer to the linked list data structure.
 * @param position The position of the element to be removed.
 * @return The item that was removed, or NULL if the item was not found.
 */
void *ll_remove(LList *ll, size_t position);

/**
 * Remove an item from the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item The item to be removed.
 * @return The item that was removed, or NULL if the item was not found.
 */
void *ll_remove_item(LList *ll, void *item, COMPARE_FUNC compare_func);

/**
 * Traverse all the items of the list and call a function for each of them.
 *
 * @param ll Pointer to the linked list data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void ll_foreach(LList *ll, ITERATOR_FUNC iterator_func, void *data);

/**
 * Check if the linked list contains an element.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare items.
 * @return true if the doubly linked list contains the element, false otherwise.
 */
bool ll_contains(LList *ll, void *item, COMPARE_FUNC compare_func);

/**
 * Search for an element and return its index in the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare items.
 * @return The first occurance of the linked list node that contains the item,
 * or NULL if the item was not found.
 */
LListNode *ll_find(LList *ll, void *item, COMPARE_FUNC compare_func);

/**
 * Reverse the linked list.
 *
 * @param ll Pointer to the linked list data structure.
 */
void ll_reverse(LList *ll);

#endif // _L_LIST_H
