#ifndef _DL_LIST_H
#define _DL_LIST_H

#include "common.h"

#include <sys/types.h>

#include <stdbool.h>
#include <stddef.h>

/**
 * The doubly linked list node.
 */
typedef struct DLListNode {
    /** The item. */
    void *item;
    /** The next node. */
    struct DLListNode *next;
    /** The previous node. */
    struct DLListNode *previous;
} DLListNode;

/**
 * The doubly linked list structure.
 */
typedef struct DLList {
    /** The head node. */
    struct DLListNode *head;
    /** The tail node. */
    struct DLListNode *tail;
} DLList;

/**
 * Initialize the doubly linked list data structure.
 *
 * @param dll Pointer to the doubly linked list data to initialize.
 * @return true if the doubly linked list data was initialized successfully,
 * false otherwise.
 */
bool dll_init(DLList *dll);

/**
 * Frees resources associated with the doubly linked list data structure.
 *
 * @param dll Pointer to the doubly linked list data to be freed.
 */
void dll_destroy(DLList *dll);

/**
 * Return the size of the doubly linked list. In order to get the size, all the
 * list items are visited, so the performance of the function is linear.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @return The size of the doubly linked list.
 */
size_t dll_size(DLList *dll);

/**
 * Check if the doubly linked list is empty.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @return true if the doubly linked list is empty, false otherwise.
 */
bool dll_is_empty(DLList *dll);

/**
 * Add an item as the first element of the doubly linked list. Note that NULL
 * items cannot be added to the list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param item Pointer to the item to add.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool dll_prepend(DLList *dll, void *item);

/**
 * Add an item as the last element of the doubly linked list. Note that NULL
 * items cannot be added to the list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param item Pointer to the item to add.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool dll_append(DLList *dll, void *item);

/**
 * Insert an item at the specified position of the doubly linked list. Note that
 * NULL items cannot be added to the list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param item Pointer to the item to add.
 * @param position The position at which the element should to be inserted. If
 * the position is bigger than or equal to the list size, the element is
 * appended to the end of the list.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool dll_insert(DLList *dll, void *item, size_t position);

/**
 * Remove the first item of the doubly linked list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @return Pointer to the item that was removed, or NULL if the list was empty.
 */
void *dll_remove_first(DLList *dll);

/**
 * Remove the last item of the doubly linked list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @return The item that was removed, or NULL if the list was empty.
 */
void *dll_remove_last(DLList *dll);

/**
 * Remove an item from the doubly linked list by position.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param position The position of the element to be removed. If the position
 * is bigger than or equal to the list size, the last element is removed.
 * @return The item that was removed, or NULL if the item was empty.
 */
void *dll_remove(DLList *dll, size_t position);

/**
 * Remove an item from the doubly linked list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param item The item to be removed.
 * @param compare_func The function used to compare the item with the list
 * items.
 * @return The item that was removed, or NULL if the item was not found.
 */
void *dll_remove_item(DLList *dll, void *item, COMPARE_FUNC compare_func);

/**
 * Traverse all the items of the doubly linked list and call a function for each
 * of them.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 * @param reverse Set to true to traverse the items in reverse.
 */
void dll_foreach(DLList *dll, ITERATOR_FUNC iterator_func, void *data,
                 bool reverse);

/**
 * Check if the doubly linked list contains an element. All the doubly linked
 * list elements are searched, so the performance of the function is linear in
 * the worst case.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare the item with the list
 * items.
 * @return true if the doubly linked list contains the element, false otherwise.
 */
bool dll_contains(DLList *dll, void *item, COMPARE_FUNC compare_func);

/**
 * Search for an element.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare items.
 * @param reverse Set to true to search in reverse.
 * @return The first occurance of the doubly linked list node that contains the
 * item, or NULL if the item was not found.
 */
DLListNode *dll_find(DLList *dll, void *item, COMPARE_FUNC compare_func,
                     bool reverse);

/**
 * Reverse the doubly linked list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 */
void dll_reverse(DLList *dll);

#endif // _DL_LIST_H
